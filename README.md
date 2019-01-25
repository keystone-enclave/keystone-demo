# keystone-demo
Demo host and enclave applications exercising most functionality.

This demo includes a small enclave server that is capable of remote
attestation, secure channel creation, and performing a simple
word-counting computation securely.

Please see documentation in the docs/ directory.

./quick-start.sh will clone/build all necessary components for the
demo to run in qemu if you have already built keystone and it's sdk
tests successfully.