LOGS_DIR = logs
DISK_IMAGE = ../busybear-linux/busybear.bin
MOUNT_DIR = ./tmp_busybear

ifndef KEYSTONE_SDK_DIR
$(error KEYSTONE_SDK_DIR is not set)
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


TCLIENT = trusted_client/client.cpp trusted_client/trusted_client.cpp

RUNTIME=eyrie-rt
EHOST= enclave-host.riscv
CCFLAGS = -I$(SDK_INCLUDE_HOST_DIR) -I$(SDK_INCLUDE_EDGE_DIR) -I$(SDK_INCLUDE_VERIFIER_DIR) -Iinclude/ -I$(SODC_INCLUDE_DIR)
LDFLAGS = -L$(SDK_LIB_DIR) -L$(SODC_LIB_DIR)

APPS = server_eapp

SRCS = $(patsubst %.riscv, %.cpp, $(EHOST))
OBJS = $(patsubst %.riscv, %.o,$(EHOST)) $(KEYSTONE_OBJ) edge_wrapper.o

TCLIENT_OBJS = $(patsubst %.cpp, %.o,$(TCLIENT))

all: makeall copysdk getandsethash trusted_client.riscv copysdk1

makeall: $(OBJS) $(SDK_HOST_LIB) $(SDK_EDGE_LIB) $(SDK_VERIFIER_LIB) $(SODC_LIB)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $(EHOST) $^
	$(foreach app, $(APPS),\
		$(MAKE) -C $(app);\
	)

trusted_client.riscv: $(TCLIENT)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $^ $(SDK_VERIFIER_LIB) $(SODC_LIB) 

%.a:
	make -C $(SDK_LIB_DIR)

$(OBJS): %.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

getandsethash:
	./scripts/get_attestation.sh ./include
	rm -rf trusted_client.riscv # We need to remove the trusted_client so that we can rebuild it with the correct values

copysdk copysdk1:
	yes | cp -rf *.riscv server_eapp/server_eapp.eapp_riscv $(KEYSTONE_SDK_DIR)/bin/
	cd $(KEYSTONE_SDK_DIR)/.. && make hifive

clean:
	rm -f *.o *.riscv
	$(foreach app, $(APPS), \
		$(MAKE) -C $(app) clean; \
	)

.PHONY: getandsethash clean