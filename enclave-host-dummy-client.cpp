#include <iostream>
#include <cstdio>
#include "keystone.h"
#include "edge_wrapper.h"
#include "encl_message.h"
#include "dummy_client.h"

/* We hardcode these for demo purposes. */
const char* enc_path = "server_eapp.eapp_riscv";
const char* runtime_path = "eyrie-rt";


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

encl_message_t wait_for_message(){

  size_t len;
  
  void* buffer = dummy_client_generate_message(&len);
  
  /* This happens here */
  encl_message_t message;
  message.host_ptr = buffer;
  message.len = len;
  return message;
}

void send_report(void* buffer, size_t len)
{
  dummy_client_get_report(buffer);
}

int main(int argc, char** argv)
{

  if(argc >= 2 && strncmp("hash",argv[1], 4) == 0){
    printf("HOST: Getting enclave hash only\n");
    dummy_client_hash_only = 1;
  }
  else{
    dummy_client_hash_only = 0;
  }
  
  /* Wait for network connection */
  dummy_client_init();
  
  Keystone enclave;
  Params params;

  params.setEnclaveEntry(0x1000);

  if(enclave.init(enc_path, runtime_path, params) != KEYSTONE_SUCCESS){
    printf("HOST: Unable to start enclave\n");
    exit(-1);
  }

  edge_init(&enclave);

  int rval = enclave.run();
  printf("rval: %i\n",rval);

  return 0;
}

