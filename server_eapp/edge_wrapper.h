#ifndef _EDGE_WRAPPER_H_
#define _EDGE_WRAPPER_H_
#include "edge_call.h"

void edge_init();

unsigned long ocall_print_buffer(char* data);
void ocall_print_value(unsigned long val);
edge_data_t ocall_wait_for_message();
void ocall_wait_for_client_pubkey(unsigned char* pk, size_t len);
void ocall_send_report(char* buffer, size_t len);
void ocall_send_reply(unsigned char* data, size_t len);
#endif /* _EDGE_WRAPPER_H_ */
