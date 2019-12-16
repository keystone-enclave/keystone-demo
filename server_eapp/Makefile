ifndef KEYSTONE_SDK_DIR
$(error KEYSTONE_SDK_DIR is not set)
endif

ifndef LIBSODIUM_DIR
$(error LIBSODIUM_DIR is not set)
endif

APP = server_eapp
APP_C_SRCS= server_eapp.c calculator.c channel.c ocalls_eapp.c

CC = riscv64-unknown-linux-gnu-gcc
CFLAGS = -Wall -Werror
LINK = riscv64-unknown-linux-gnu-ld
AS = riscv64-unknown-linux-gnu-as

SDK_LIB_DIR = $(KEYSTONE_SDK_DIR)/lib
SDK_APP_LIB = $(SDK_LIB_DIR)/libkeystone-eapp.a
SDK_EDGE_LIB = $(SDK_LIB_DIR)/libkeystone-edge.a
SDK_INCLUDE_APP_DIR = $(SDK_LIB_DIR)/app/include
SDK_INCLUDE_EDGE_DIR = $(SDK_LIB_DIR)/edge/include

SOD_INCLUDE_DIR = $(LIBSODIUM_DIR)/include
SOD_LIB_DIR = $(LIBSODIUM_DIR)/.libs
SOD_LIB = $(SOD_LIB_DIR)/libsodium.a

FLATCC_INCLUDE_DIR = $(KEYEDGE_DIR)/flatcc/include
FLATCC_LIB = $(KEYEDGE_DIR)/lib/flatccrt.a
KEYEDGE_INCLUDE_DIR = $(KEYEDGE_DIR)/target/include

LDFLAGS = -static -L$(SDK_LIB_DIR) -L$(SOD_LIB_DIR) -L$(KEYEDGE_DIR)/lib
CFLAGS += -I$(SDK_INCLUDE_APP_DIR) -I$(SDK_INCLUDE_EDGE_DIR) -I../include -I../keyedge -I$(SOD_INCLUDE_DIR) -I$(KEYEDGE_INCLUDE_DIR) -I$(FLATCC_INCLUDE_DIR)

APP_C_OBJS = $(patsubst %.c,%.o, $(APP_C_SRCS))
APP_A_OBJS = $(patsubst %.s,%.o, $(APP_A_SRCS))
APP_LDS ?= ../app.lds

APP_BIN = $(patsubst %,%.eapp_riscv,$(APP))

all: $(APP_BIN)

$(APP_C_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $<

$(APP_BIN): %.eapp_riscv : $(APP_C_OBJS) $(APP_A_OBJS) $(SDK_APP_LIB) $(SDK_EDGE_LIB) $(SOD_LIB)
	$(LINK) $(LDFLAGS) --start-group $^ $(FLATCC_LIB) --end-group -T $(APP_LDS) -o $@
	chmod -x $@

clean:
	rm -f *.o $(APP_BIN) $(EXTRA_CLEAN)

