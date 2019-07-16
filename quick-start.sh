#!/bin/bash

echo -e "This is a quick-start build script for the Keystone Demo, it
will clone and build all the necessary parts to run the demo
server/applcation and client on a RISC-V platform (ex: qemu). Please
ensure you have cloned keystone completely and that you have fully
built the sdk tests and run them successfully in qemu.

You must set KEYSTONE_DIR to the directory of a built
keystone clone.

If you have already started building libsodium/etc, it is not
recommended to use this script."
read -r -p "Continue? [Y/n] " response
response=${response,,}
if [[ "$response" =~ ^(no|n)$ ]]
then
    exit 0
fi



# Check location/tools
if [[ ! -v KEYSTONE_DIR ]]
then
    echo "KEYSTONE_DIR not set! Please set this to the location of the keystone checkout!"
    exit 0
fi

export KEYSTONE_SDK_DIR=$KEYSTONE_DIR/sdk

DEMO_DIR=$(pwd)

set -e

mkdir -p libsodium_builds
cd libsodium_builds

# Clone, checkout, and build the server libsodium
git clone https://github.com/jedisct1/libsodium.git libsodium_server
cd libsodium_server
git checkout 4917510626c55c1f199ef7383ae164cf96044aea
patch -p1 < $DEMO_DIR/sodium_patches/configure.ac.patch
./autogen.sh
./configure --host=riscv64-unknown-linux-gnu --disable-ssp --disable-asm --without-pthreads
make
export LIBSODIUM_DIR=$(pwd)/src/libsodium/
cd ..

# Clone, checkout, and build the client libsodium
git clone https://github.com/jedisct1/libsodium.git libsodium_client
cd libsodium_client
git checkout 4917510626c55c1f199ef7383ae164cf96044aea
./configure --host=riscv64-unknown-linux-gnu --disable-ssp --disable-asm --without-pthreads
make
export LIBSODIUM_CLIENT_DIR=$(pwd)/src/libsodium/
cd ..

cd ..

# Copy the expected hash over
echo "Copying expected sm hash from riscv-pk, this may be incorrect!"
cp $KEYSTONE_SDK_DIR/../riscv-pk/hash/*.h include/

# Build the demo
make
make trusted_client.riscv

# Copy the demo files
make copybins

# Done!

echo -e "************ Demo binaries built and copied into sdk bins directory. ***************
            Run 'make' in the top-level of keystone, and the demo binaries should
            be available in qemu next time you start it!"
