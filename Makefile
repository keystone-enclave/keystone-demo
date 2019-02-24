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
	rm -rf $(LOGS_DIR)
	./scripts/extract_hash.sh
	mkdir -p $(LOGS_DIR)
	mkdir -p $(MOUNT_DIR)
	sudo mount $(DISK_IMAGE) $(MOUNT_DIR)
	sudo rsync -a $(MOUNT_DIR)/root/ $(LOGS_DIR)/tmp
	rm -rf $(MOUNT_DIR)/root/*.log
	sudo umount $(MOUNT_DIR)
	rmdir $(MOUNT_DIR)
	mv $(LOGS_DIR)/tmp/*.log $(LOGS_DIR)
	rm -rf $(LOGS_DIR)/tmp
	awk '/=== Security Monitor ===/,/=== Enclave Application ===/' $(LOGS_DIR)/cout.log  | grep "Hash: " | cut -c 7- > include/sm.hash
	cd include && ./genhash.sh self sm
	rm -f include/sm.hash
	awk '/=== Enclave Application ===/,/-- Device pubkey --/' $(LOGS_DIR)/cout.log  | grep "Hash: " | cut -c 7- > include/enclave.hash
	cd include && ./genhash.sh self enclave
	rm -f include/enclave.hash
	rm -rf $(LOGS_DIR)

copysdk copysdk1:
	cp -u *.riscv server_eapp/server_eapp.eapp_riscv $(KEYSTONE_SDK_DIR)/bin/
	cd $(KEYSTONE_SDK_DIR) && make copy-tests

clean:
	rm -f *.o *.riscv
	$(foreach app, $(APPS), \
		$(MAKE) -C $(app) clean; \
	)

.PHONY: getandsethash clean