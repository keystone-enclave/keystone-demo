#ifndef _EDGE_WRAPPER_H_
#define _EDGE_WRAPPER_H_
#include "edge_call.h"

void edge_init();

unsigned long ocall_print_buffer(char* data, size_t data_len);
void ocall_print_value(unsigned long val);
edge_data_t ocall_wait_for_message();
#endif /* _EDGE_WRAPPER_H_ */
