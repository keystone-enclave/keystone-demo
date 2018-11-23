
#include "dummy_client.h"
#include "sodium.h"
unsigned char client_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char client_sk[crypto_kx_SECRETKEYBYTES];
unsigned char server_pk[crypto_kx_PUBLICKEYBYTES];


void dummy_client_init(){

  if( sodium_init() != 0){
    printf("SODIUM INIT FAILURE\n");
    exit(-1);
  }
  if( crypto_kx_keypair(client_pk,client_sk) != 0){
    printf("SODIUM KX INIT FAILURE\n");
    exit(-1);
  }
}

void* dummy_client_pubkey(){
  return (void*)client_pk;
}

void dummy_client_get_report(void* buffer){
}

const char* longstr = "hello hello hello hello hello hello hello hello hello hello";

void* dummy_client_generate_message(size_t* len){
  /* Generate plaintext */
  size_t datalen = strlen(longstr)+1; 
  calc_message_t* calc_msg = (calc_message_t*)malloc(sizeof(calc_message_t) + datalen);
  calc_msg->msg_type = CALC_MSG_WORDCOUNT;
  calc_msg->len = datalen;
  memcpy(calc_msg->msg, (void*)longstr, calc_msg->len);
  size_t totalsize = calc_msg->len + sizeof(calc_message_t);

  *len = totalsize;



  return (void*)calc_msg;
  
  
}

int dummy_client_read_reply(){
  
}
