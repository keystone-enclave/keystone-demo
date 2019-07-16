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


TCLIENT_SRCS = trusted_client/client.cpp trusted_client/trusted_client.cpp include/enclave_expected_hash.h include/sm_expected_hash.h
TCLIENT = trusted_client.riscv
RUNTIME = eyrie-rt
EHOST= enclave-host.riscv
SERVER = server_eapp/server_eapp.eapp_riscv

CCFLAGS = -I$(SDK_INCLUDE_HOST_DIR) -I$(SDK_INCLUDE_EDGE_DIR) -I$(SDK_INCLUDE_VERIFIER_DIR) -Iinclude/ -I$(SODC_INCLUDE_DIR)
LDFLAGS = -L$(SDK_LIB_DIR) -L$(SODC_LIB_DIR)



SRCS = $(patsubst %.riscv, %.cpp, $(EHOST))
OBJS = $(patsubst %.riscv, %.o,$(EHOST)) $(KEYSTONE_OBJ) edge_wrapper.o

all: $(EHOST) $(TCLIENT) $(SERVER) $(RUNTIME)

$(EHOST): $(OBJS) $(SDK_HOST_LIB) $(SDK_EDGE_LIB) $(SDK_VERIFIER_LIB) $(SODC_LIB)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $(EHOST) $^

.PHONY:
$(SERVER):
	$(MAKE) -C `dirname $(SERVER)`

$(TCLIENT): $(TCLIENT_SRCS)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $^ $(SDK_VERIFIER_LIB) $(SODC_LIB)

$(RUNTIME):
	$(KEYSTONE_SDK_DIR)/rts/eyrie/build.sh
	cp $(KEYSTONE_SDK_DIR)/rts/eyrie/eyrie-rt .

%.a:
	make -C $(SDK_LIB_DIR)

$(OBJS): %.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

build-hash-using-qemu: all copybins getandsethash

getandsethash:
	./scripts/get_attestation.sh ./include

copybins:
	mkdir -p $(KEYSTONE_DIR)/buildroot_overlay/root/keystone-demo/
	cp $(TCLIENT) $(EHOST) $(SERVER) $(RUNTIME) $(KEYSTONE_DIR)/buildroot_overlay/root/keystone-demo/
	cd $(KEYSTONE_DIR) && make

clean:
	rm -f *.o *.riscv
	rm -f eyrie-rt
	$(foreach app, $(APPS), \
		$(MAKE) -C $(app) clean; \
	)

.PHONY: getandsethash clean
