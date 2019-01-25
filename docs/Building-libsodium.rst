Building libsodium
==================

We need to build 2 different copies of libsodium, one for running on
the trusted_client, and one for the enclave app.

I'm currently working off libsodium stable branch, commit:
4917510626c55c1f199ef7383ae164cf96044aea

The quick-start script will build all copies of libsodium in a
libsodium_builds subdir.

Server/eapp libsodium
---------------------
This is the trickier one. We need to patch configure.ac, and then
regenerate the configure script, and rebuild.

do approximately the following::
  git clone https://github.com/jedisct1/libsodium.git libsodium_server
  cd libsodium_server
  git checkout 4917510626c55c1f199ef7383ae164cf96044aea
  patch -p1 < $DEMO_DIR/sodium_patches/configure.ac.patch
  ./autogen.sh
  ./configure --host=riscv64-unknown-linux-gnu --disable-ssp --disable-asm --without-pthreads
  make
  export LIBSODIUM_DIR=$(pwd)/src/libsodium/

Client libsodium
----------------

No patches needed, regardless of if you are building x86 or RISCV
client libsodium.

For RISCV do approximately the following::
  git clone https://github.com/jedisct1/libsodium.git libsodium_client
  cd libsodium_client
  git checkout 4917510626c55c1f199ef7383ae164cf96044aea
  ./configure --host=riscv64-unknown-linux-gnu --disable-ssp --disable-asm --without-pthreads
  make
  export LIBSODIUM_CLIENT_DIR=$(pwd)/src/libsodium/

