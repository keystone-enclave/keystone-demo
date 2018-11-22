#include <iostream>
#include <cstdio>
#include "keystone.h"
#include "edge_wrapper.h"
#include "encl_message.h"
#include "calculator.h"

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
  calc_message_t calc_msg;
  calc_msg.msg_type = CALC_MSG_WORDCOUNT;
  calc_msg.len = strlen(longstr)+1;
  void* tmpbuf = malloc(calc_msg.len + sizeof(calc_message_t));
  memcpy(tmpbuf, (void*)&calc_msg, sizeof(calc_message_t));
  memcpy(tmpbuf+sizeof(calc_message_t), (void*)longstr, calc_msg.len);
  size_t tmpsize = calc_msg.len + sizeof(calc_message_t);

  /* This happens here */
  encl_message_t message;
  message.host_ptr = tmpbuf;
  message.len = tmpsize;
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
  Keystone enclave;
  Params params;

  params.setEnclaveEntry(0x1000);

  enclave.init(argv[1], argv[2], params);

  edge_init(&enclave);

  enclave.run();

  return 0;
}

