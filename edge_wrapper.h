#ifndef _EDGE_WRAPPER_H_
#define _EDGE_WRAPPER_H_

#include <edge_call.hpp>
#include "keystone.h"

typedef struct encl_message_t {
  void* host_ptr;
  size_t len;  
} encl_message_t;

int edge_init(Keystone* enclave);

void print_buffer_wrapper(void* buffer, size_t buffer_len);
unsigned long print_buffer(char* str);

void print_value_wrapper(void* shared_buffer, size_t shared_buffer_size);
void print_value(unsigned long val);

void copy_report_wrapper(void* shared_buffer, size_t shared_buffer_size);
void copy_report(void* shared_buffer);

void wait_for_message_wrapper(void* shared_buffer, size_t shared_buffer_size);
encl_message_t wait_for_message();

void send_reply_wrapper(void* shared_buffer, size_t shared_buffer_size);
void send_reply(edge_data_t message);

#endif /* _EDGE_WRAPPER_H_ */
