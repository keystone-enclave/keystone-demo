# keystone-demo
Demo host and enclave applications exercising most functionality.

This demo includes a small enclave server that is capable of remote
attestation, secure channel creation, and performing a simple
word-counting computation securely.

Please see documentation in the docs/ directory.

./quick-start.sh will clone/build all necessary components for the
demo to run in qemu if you have already built keystone and it's sdk
tests successfully.

The demo will generally work on the master branch of Keystone, but
will ALWAYS work on the dev branch. We suggest building the dev branch
of Keystone if you have any issues with the demo on master.

# Quick Start

The demo requires the expected hash of the security monitor.
The hash will be used by the trusted client to verify that the server enclave
is created and initialized by the known version of the SM.

If you want to skip this verification, you can pass in `--ignore-valid` flag
to the client.

Please see the security monitor's documentation to see how to generate a hash.

Once you generated the `sm_expected_hash.h`, try:

```
SM_HASH=<path/to/sm_expected_hash.h> ./quick-start.sh
```

You should be able to see the server enclave package `demo-server.ke` and the
trusted client `trusted_client.riscv` under `build` directory.

Copy these files into the machine, and run the server enclave.
Then, connect to the server using the client.

```
# on the server side
./demo-server.ke
```

```
# on the client side
./trusted_client.riscv
```

The client will connect to the enclave and perform the remote attestation.
If the attestation is successful, the client can send an arbitrary message to the server
so that the server counts the number of words in the message and reply.

## Attestation Failures

It is expected that the client will reject the attestation report from
the host if you haven't regenerated the expected hashes for the SM and
eapp. Pass the `--ignore-valid` flag to the client for testing.
