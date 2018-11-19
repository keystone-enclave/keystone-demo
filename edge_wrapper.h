#ifndef _EDGE_WRAPPER_H_
#define _EDGE_WRAPPER_H_

#include <edge_call.hpp>
#include "keystone.h"

typedef struct encl_message_t {
  void* host_ptr;
  size_t len;  
} encl_message_t;

int edge_init(Keystone* enclave);

void print_buffer_wrapper(void* buffer);
unsigned long print_buffer(char* str);

void print_value_wrapper(void* buffer);
void print_value(unsigned long val);

void copy_report_wrapper(void* buffer);
void copy_report(void* shared_buffer);

void wait_for_message_wrapper(void* buffer);
encl_message_t wait_for_message();

void send_reply_wrapper(void* buffer);
void send_reply(void* message, size_t len);

#endif /* _EDGE_WRAPPER_H_ */
