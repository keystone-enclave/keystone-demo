

Keystone Demo
=============

The Keystone Demo is an example of the current capabilities of the
Keystone enclave framework. The demo consists of:

 - A server application (server-eapp)
 - An untrusted host (enclave-host)
 - A remote client for demonstration of full remote attestation (trusted-client)

This demo shows how a remote client can request computation to be
performed on an untrusted server using an enclave.

Note: The demo uses test keys and is not safe for production use.

We suggest using the keystone:dev branch since the demo is generally
updated to work with the most-current version of Keystone.

Server eapp
-----------

The demo server enclave application, basic enclave features
(attestation report generation, etc), a simple word-counting feature,
and uses ``libsodium`` for establishing a secure channel.

The enclave first sends a copy of its attestation report, along with
its eccdh public key to the client. Upon receving the client public
key, it establishes a secure channel and asks the enclave-host to wait
for messages.

Once it has received a message, it authenticates and decrypts the
message.

If successful, it supports two message types:

 #. word-count of arbitrarily sized block of text
 #. exit

For word count, it performs a simple word counting calculation, and
returns the result over the secure channel.

Enclave host
------------

The host serves two functions: starting the enclave, and proxying
network messages.

Trusted Client
--------------

A simple remote client that connects to the host, validates the
enclave report, constructs a secure channel, and then can send
messages to the host for computation.
