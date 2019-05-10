ifndef KEYSTONE_DIR
$(error KEYSTONE_DIR is not set)
endif

ifndef KEYSTONE_SDK_DIR
export KEYSTONE_SDK_DIR = $(KEYSTONE_DIR)/sdk
endif

ifndef LIBSODIUM_CLIENT_DIR
$(error LIBSODIUM_CLIENT_DIR is not set)
endif

CC = riscv64-unknown-linux-gnu-g++
OBJCOPY = riscv64-unknown-linux-gnu-objcopy

SDK_LIB_DIR = $(KEYSTONE_SDK_DIR)/lib
SDK_HOST_LIB = $(SDK_LIB_DIR)/libkeystone-host.a
SDK_EDGE_LIB = $(SDK_LIB_DIR)/libkeystone-edge.a
SDK_VERIFIER_LIB = $(SDK_LIB_DIR)/libkeystone-verifier.a

SDK_INCLUDE_HOST_DIR = $(SDK_LIB_DIR)/host/include
SDK_INCLUDE_EDGE_DIR = $(SDK_LIB_DIR)/edge/include
SDK_INCLUDE_VERIFIER_DIR = $(SDK_LIB_DIR)/verifier

SODC_INCLUDE_DIR = $(LIBSODIUM_CLIENT_DIR)/include
SODC_LIB_DIR = $(LIBSODIUM_CLIENT_DIR)/.libs
SODC_LIB = $(SODC_LIB_DIR)/libsodium.a

SOD_LIB_DIR = $(LIBSODIUM_DIR)/.libs
SOD_LIB = $(SOD_LIB_DIR)/libsodium.a


TCLIENT = trusted_client/client.cpp trusted_client/trusted_client.cpp include/enclave_expected_hash.h include/sm_expected_hash.h

RUNTIME=eyrie-rt
EHOST= enclave-host.riscv
CCFLAGS = -I$(SDK_INCLUDE_HOST_DIR) -I$(SDK_INCLUDE_EDGE_DIR) -I$(SDK_INCLUDE_VERIFIER_DIR) -Iinclude/ -I$(SODC_INCLUDE_DIR)
LDFLAGS = -L$(SDK_LIB_DIR) -L$(SODC_LIB_DIR)

APPS = server_eapp

SRCS = $(patsubst %.riscv, %.cpp, $(EHOST))
OBJS = $(patsubst %.riscv, %.o,$(EHOST)) $(KEYSTONE_OBJ) edge_wrapper.o

TCLIENT_OBJS = $(patsubst %.cpp, %.o,$(TCLIENT))

all: $(OBJS) $(SDK_HOST_LIB) $(SDK_EDGE_LIB) $(SDK_VERIFIER_LIB) $(SODC_LIB)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $(EHOST) $^
	$(foreach app, $(APPS),\
		$(MAKE) -C $(app);\
	)

aestest: $(OBJS) $(SDK_HOST_LIB) $(SDK_EDGE_LIB) $(SDK_VERIFIER_LIB) $(SODC_LIB)
	$(CC) -static -I/home/dkohlbre/keystone/keystone/keystone-demo/libsodium_builds/libsodium_client/test/quirks/ $(CCFLAGS) -L$(SDK_LIB_DIR) -L$(SOD_LIB_DIR) -o aestest /home/dkohlbre/keystone/keystone/keystone-demo/libsodium_builds/libsodium_server/test/default/aead_aes256gcm.c $(SOD_LIB)

trusted_client.riscv: $(TCLIENT)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $^ $(SDK_VERIFIER_LIB) $(SODC_LIB)

%.a:
	make -C $(SDK_LIB_DIR)

$(OBJS): %.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

build-hash-using-qemu: all copysdk getandsethash trusted_client.riscv

getandsethash:
	./scripts/get_attestation.sh ./include

copysdk:
	cp *.riscv server_eapp/server_eapp.eapp_riscv $(KEYSTONE_SDK_DIR)/bin/
	cd $(KEYSTONE_SDK_DIR)/.. && make hifive

clean:
	rm -f *.o *.riscv
	$(foreach app, $(APPS), \
		$(MAKE) -C $(app) clean; \
	)

.PHONY: getandsethash clean
