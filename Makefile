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
EHOST= enclave-host.riscv #enclave-host-dummy-client.riscv
CCFLAGS = -I$(SDK_INCLUDE_HOST_DIR) -I$(SDK_INCLUDE_EDGE_DIR) -I$(SDK_INCLUDE_VERIFIER_DIR) -Iinclude/ -I$(SODC_INCLUDE_DIR)
LDFLAGS = -L$(SDK_LIB_DIR) -L$(SODC_LIB_DIR)

APPS = server_eapp

SRCS = $(patsubst %.riscv, %.cpp, $(EHOST))
OBJS = $(patsubst %.riscv, %.o,$(EHOST)) $(KEYSTONE_OBJ) edge_wrapper.o #dummy_client.o

TCLIENT_OBJS = $(patsubst %.cpp, %.o,$(TCLIENT))

all:  $(OBJS) $(SDK_HOST_LIB) $(SDK_EDGE_LIB) $(SDK_VERIFIER_LIB) $(SODC_LIB)
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

clean:
	rm -f *.o *.riscv
	$(foreach app, $(APPS), \
		$(MAKE) -C $(app) clean; \
	)
