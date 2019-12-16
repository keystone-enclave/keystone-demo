#ifndef _EDGE_WRAPPER_H_
#define _EDGE_WRAPPER_H_

typedef unsigned long size_t;

#include <ocalls_header.h>

#define crypto_kx_PUBLICKEYBYTES 32

typedef struct report {
	char data[2048];
} report;

typedef struct pubkey {
	char data[crypto_kx_PUBLICKEYBYTES];
} pubkey;

typedef struct encl_message_t {
  keyedge_vla void* host_ptr;
  keyedge_size size_t len;
} encl_message_t;

unsigned long print_buffer(keyedge_str char* str);
void print_value(unsigned long val);
void end_enclave();

report get_attestation_report() keyedge_inverse;
int set_client_pk(pubkey* pk) keyedge_inverse;
encl_message_t calc_message(encl_message_t msg) keyedge_inverse;

#endif /* _EDGE_WRAPPER_H_ */
