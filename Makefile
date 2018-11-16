ifndef KEYSTONE_SDK_DIR
$(error KEYSTONE_SDK_DIR is not set)
endif

CC = riscv64-unknown-linux-gnu-g++
OBJCOPY = riscv64-unknown-linux-gnu-objcopy

SDK_LIB_DIR = $(KEYSTONE_SDK_DIR)/lib
SDK_HOST_LIB = $(SDK_LIB_DIR)/libkeystone-host.a
SDK_EDGE_LIB = $(SDK_LIB_DIR)/libkeystone-edge.a
SDK_INCLUDE_HOST_DIR = $(SDK_LIB_DIR)/host/include
SDK_INCLUDE_EDGE_DIR = $(SDK_LIB_DIR)/edge/include

RUNTIME=eyrie-rt
EHOST=enclave-host.riscv
CCFLAGS = -I$(SDK_INCLUDE_HOST_DIR) -I$(SDK_INCLUDE_EDGE_DIR)
LDFLAGS = -L$(SDK_LIB_DIR)

APPS = clients

SRCS = $(patsubst %.riscv, %.cpp, $(EHOST))
OBJS = $(patsubst %.riscv, %.o,$(EHOST)) $(KEYSTONE_OBJ) edge_wrapper.o

all:  $(OBJS) $(SDK_HOST_LIB) $(SDK_EDGE_LIB) 
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $(EHOST) $^
	$(foreach app, $(APPS),\
		$(MAKE) -C $(app);\
	)

$(SDK_HOST_LIB):
	make -C $(SDK_HOST_DIR)

$(OBJS): %.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o *.riscv test
	$(foreach test, $(TESTS), \
		$(MAKE) -C $(test) clean; \
	)
