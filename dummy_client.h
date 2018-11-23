#ifndef _DUMMY_CLIENT_H_
#define _DUMMY_CLIENT_H_
#include <iostream>
#include <cstdio>
#include "keystone.h"
#include "calc_msg.h"

void dummy_client_init();
void* dummy_client_pubkey();
void* dummy_client_generate_message( size_t* len);
int dummy_client_read_reply();


#endif /* _DUMMY_CLIENT_H_ */
