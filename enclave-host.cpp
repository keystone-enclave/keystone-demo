#include <iostream>
#include <cstdio>
#include "keystone.h"
#include "edge_wrapper.h"
#include "encl_message.h"
#include "dummy_client.h"

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

void* wait_for_client_pubkey(){
  return dummy_client_pubkey();
}

/* Buffer must be free'd after this */
encl_message_t wait_for_message(){

  size_t len;
  
  void* buffer = dummy_client_generate_message(&len);
  
  /* This happens here */
  encl_message_t message;
  message.host_ptr = buffer;
  message.len = len;
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

