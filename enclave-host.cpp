#include <iostream>
#include <cstdio>
#include "keystone.h"
#include "edge_wrapper.h"
#include "encl_message.h"
#include "calc_msg.h"

const char* longstr = "hello hello hello hello hello hello hello hello hello hello";

unsigned long print_buffer(char* str){
  printf("Enclave said: %s",str);
  return strlen(str);
}

void print_value(unsigned long val){
  printf("Enclave said value: %u\n",val);
  return;
}

void send_reply(void* data, size_t len){
  printf("GOT A MESSAGE FROM ENCLAVE\n");
}

encl_message_t wait_for_message(){

  /* This all will happen on the remote */
  size_t datalen = strlen(longstr)+1; 
  calc_message_t* calc_msg = (calc_message_t*)malloc(sizeof(calc_message_t) + datalen);
  calc_msg->msg_type = CALC_MSG_WORDCOUNT;
  calc_msg->len = datalen;
  memcpy(calc_msg->msg, (void*)longstr, calc_msg->len);
  size_t totalsize = calc_msg->len + sizeof(calc_message_t);

  /* This happens here */
  encl_message_t message;
  message.host_ptr = calc_msg;
  message.len = totalsize;
  return message;
}

void print_hex(void* buffer, size_t len)
{
  int i;
  for(i = 0; i < len; i+=sizeof(uintptr_t))
  {
    printf("%.16lx ", *((uintptr_t*) ((uintptr_t)buffer + i)));
  }
  printf("\n");
}

void copy_report(void* buffer)
{
  Report report;
  report.fromBytes((unsigned char*)buffer);

  report.printJson();
  if (report.verify((void*) "data", 4))
  {
    printf("Attestation report is valid\n");
  }
  else
  {
    printf("Attestation report is not valid\n");
  }
}

int main(int argc, char** argv)
{
  if(argc != 3)
  {
    printf("Usage: %s <eapp> <runtime>\n", argv[0]);
    return 0;
  }

  /* Wait for network connection */

  Keystone enclave;
  Params params;

  params.setEnclaveEntry(0x1000);

  enclave.init(argv[1], argv[2], params);

  edge_init(&enclave);

  int rval = enclave.run();
  printf("rval: %i\n",rval);

  return 0;
}

