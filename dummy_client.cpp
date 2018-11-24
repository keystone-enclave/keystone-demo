
#include "dummy_client.h"
#include "sodium.h"
unsigned char client_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char client_sk[crypto_kx_SECRETKEYBYTES];
unsigned char server_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char rx[crypto_kx_SESSIONKEYBYTES];
unsigned char tx[crypto_kx_SESSIONKEYBYTES];



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

  Report report;
  report.fromBytes((unsigned char*)buffer);
  report.printJson();
  if (report.verify())
  {
    printf("DC:Attestation report is valid\n");
  }
  else
  {
    printf("DC:Attestation report is NOT valid\n");
  }

  // TODO Error case

  if(report.getDataSize() !=  crypto_kx_PUBLICKEYBYTES){
    //  TODO ERROR
    printf("DC: Bad report data sec size\n");
  }

  memcpy(server_pk, report.getDataSection(), crypto_kx_PUBLICKEYBYTES);

  if(crypto_kx_client_session_keys(rx, tx, client_pk, client_sk, server_pk) != 0) {
    // TODO ERROR
    printf("DC: Bad session keygen\n");
  }
  
  printf("DC: Keygen stage done\n");
  
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
