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
  dummy_client_read_reply((unsigned char*)data, len);
}

void* wait_for_client_pubkey(){
  return dummy_client_pubkey();
}


/* TODO Buffer must be free'd after this */
encl_message_t wait_for_message(){

  size_t len;
  
  void* buffer = dummy_client_generate_message(&len);
  
  /* This happens here */
  encl_message_t message;
  message.host_ptr = buffer;
  message.len = len;
  return message;
}

void send_report(void* buffer)
{
  dummy_client_get_report(buffer);
}

int main(int argc, char** argv)
{
  if(argc != 3)
  {
    printf("Usage: %s <eapp> <runtime>\n", argv[0]);
    return 0;
  }

  /* Wait for network connection */
  dummy_client_init();
  
  Keystone enclave;
  Params params;

  params.setEnclaveEntry(0x1000);

  enclave.init(argv[1], argv[2], params);

  edge_init(&enclave);

  int rval = enclave.run();
  printf("rval: %i\n",rval);

  return 0;
}

