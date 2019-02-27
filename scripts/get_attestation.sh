#!/bin/bash

if [ -z "$KEYSTONE_SDK_DIR" -a "${KEYSTONE_SDK_DIR+xxx}" = "xxx" ]; then
    echo You MUST set KEYSTONE_SDK_DIR.;
fi
if [ -z "$KEYSTONE_DIR" -a "${KEYSTONE_DIR+xxx}" = "xxx" ]; then
    echo You MUST set KEYSTONE_DIR.;
fi

LOGS_DIR="logs"
DISK_IMAGE="$KEYSTONE_DIR/busybear-linux/busybear.bin"
MOUNT_DIR="./tmp_busybear"

copysdk () {
    curdir="$(ls -1)"
    cp -u *.riscv server_eapp/server_eapp.eapp_riscv $KEYSTONE_SDK_DIR/bin/
	cd $KEYSTONE_SDK_DIR
	make copy-tests
	cd $curdir
}

genhash () {
    echo "Generating hash ($2) for \"$1\""
    echo $2 | xxd -r -p - > $1_expected_hash
    xxd -i $1_expected_hash > $1_expected_hash.h
}

copysdk
./extract_hash.sh
mkdir -p $LOGS_DIR
mkdir -p $MOUNT_DIR
sudo mount $DISK_IMAGE $MOUNT_DIR
sudo rsync -a $MOUNT_DIR/root/ $LOGS_DIR/tmp
rm -rf $MOUNT_DIR/root/*.log
sudo umount $MOUNT_DIR
rmdir $MOUNT_DIR
mv $LOGS_DIR/tmp/*.log $LOGS_DIR
rm -rf $LOGS_DIR/tmp
SM_HASH=$(awk '/=== Security Monitor ===/,/=== Enclave Application ===/' $LOGS_DIR/cout.log  | grep "Hash: " | cut -c 7-)
EAPP_HASH=$(awk '/=== Enclave Application ===/,/-- Device pubkey --/' $(LOGS_DIR)/cout.log  | grep "Hash: " | cut -c 7-)
cd include
genhash sm SM_HASH
genhash enclave EAPP_HASH
cd ..
rm -rf $(LOGS_DIR)
copysdk