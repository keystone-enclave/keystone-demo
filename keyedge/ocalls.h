#ifndef _EDGE_WRAPPER_H_
#define _EDGE_WRAPPER_H_

typedef unsigned long size_t;

#include <ocalls_header.h>

#define crypto_kx_PUBLICKEYBYTES 32

typedef struct pubkey {
	char data[crypto_kx_PUBLICKEYBYTES];
} pubkey;

typedef struct encl_message_t {
  keyedge_vla void* host_ptr;
  keyedge_size size_t len;
} encl_message_t;

unsigned long print_buffer(keyedge_str char* str);
void print_value(unsigned long val);
void send_report(keyedge_vla void* shared_buffer, keyedge_size size_t len);
encl_message_t wait_for_message();
void send_reply(keyedge_vla void* message, keyedge_size size_t len);
pubkey* wait_for_client_pubkey();

#endif /* _EDGE_WRAPPER_H_ */
