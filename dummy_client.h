#ifndef _DUMMY_CLIENT_H_
#define _DUMMY_CLIENT_H_
#include <iostream>
#include <cstdio>
#include "keystone.h"
#include "calc_msg.h"
#include "report.h"

void dummy_client_init();
void* dummy_client_pubkey();
void* dummy_client_generate_message( size_t* len);
int dummy_client_read_reply();
void dummy_client_get_report(void* buffer);

#endif /* _DUMMY_CLIENT_H_ */
