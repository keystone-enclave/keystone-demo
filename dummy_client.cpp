#include <string>
#include <iostream>
#include <fstream>
#include "dummy_client.h"
#include "sodium.h"

#include "test_dev_key.h"
#include "enclave_expected_hash.h"
#include "sm_expected_hash.h"

unsigned char client_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char client_sk[crypto_kx_SECRETKEYBYTES];
unsigned char server_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char rx[crypto_kx_SESSIONKEYBYTES];
unsigned char tx[crypto_kx_SESSIONKEYBYTES];

calc_message_t* calc_msg;
int msg_count;
#define MAX_MSGS 50

int dummy_client_hash_only;

void dummy_client_exit(){
  printf("DC: Fatal errot, exiting\n");
  exit(-1);
}

void dummy_client_init(){

  if( sodium_init() != 0){
    printf("DC: Libsodium init failure\n");
    dummy_client_exit();
  }
  if( crypto_kx_keypair(client_pk,client_sk) != 0){
    printf("DC: Libsodium keypair gen failure\n");
    dummy_client_exit();
  }

  msg_count = 0;
  calc_msg = NULL;
}

void* dummy_client_pubkey(){
  return (void*)client_pk;
}

void dummy_client_get_report(void* buffer){

  Report report;
  report.fromBytes((unsigned char*)buffer);
  std::cout << "Enclave hash: " << report.BytesToHex(report.getEnclaveHash(),MDSIZE) << std::endl;
  if(dummy_client_hash_only){
    exit(0);
  }

  if (report.verify(enclave_expected_hash,
		    sm_expected_hash,
		    _sanctum_dev_public_key))
  {
    printf("DC:Attestation signature and enclave hash are valid\n");
  }
  else
  {
    report.printJson();
    printf("DC:Attestation report is NOT valid\n");
    dummy_client_exit();
  }

  if(report.getDataSize() !=  crypto_kx_PUBLICKEYBYTES){
    printf("DC: Bad report data sec size\n");
    dummy_client_exit();
  }

  memcpy(server_pk, report.getDataSection(), crypto_kx_PUBLICKEYBYTES);

  if(crypto_kx_client_session_keys(rx, tx, client_pk, client_sk, server_pk) != 0) {
    printf("DC: Bad session keygen\n");
    dummy_client_exit();
  }
  
  printf("DC: Keygen stage done\n");
  
}

const char* longstr = "hello hello hello hello hello hello hello hello hello hello";



void* dummy_client_generate_message(size_t* len){
  /* Generate plaintext */
  size_t totalsize;

  // Free previously allocated message
  if(calc_msg != NULL)
    free(calc_msg);
  
  if(msg_count < MAX_MSGS){
    size_t datalen = strlen(longstr)+1;
    size_t buffersize = sizeof(calc_message_t) + datalen + crypto_secretbox_MACBYTES + crypto_secretbox_NONCEBYTES;
    calc_msg = (calc_message_t*)malloc(buffersize);
    if(calc_msg == NULL)
      dummy_client_exit();
    calc_msg->msg_type = CALC_MSG_WORDCOUNT;
    calc_msg->len = datalen;
    memcpy(calc_msg->msg, (void*)longstr, calc_msg->len);
    totalsize = calc_msg->len + sizeof(calc_message_t);

    msg_count++;
  }
  else{
    calc_msg = (calc_message_t*)malloc(sizeof(calc_message_t) + crypto_secretbox_MACBYTES + crypto_secretbox_NONCEBYTES);
    if(calc_msg == NULL)
      dummy_client_exit();
    calc_msg->msg_type = CALC_MSG_EXIT;
    calc_msg->len = 0;
    totalsize = sizeof(calc_message_t);
  }    
  /* Encrypt */
  dummy_client_box((unsigned char*)calc_msg, totalsize, len);
  return (void*)calc_msg;
}

void dummy_client_box(unsigned char* buffer, size_t size, size_t* finalsize){
  unsigned char* nonceptr = &(buffer[crypto_secretbox_MACBYTES+size]);
  randombytes_buf(nonceptr, crypto_secretbox_NONCEBYTES);

  *finalsize = size + crypto_secretbox_MACBYTES + crypto_secretbox_NONCEBYTES;
  
  if(crypto_secretbox_easy(buffer, buffer, size, nonceptr, tx) != 0){
    printf("DC: secretbox failed\n");
  }
  
}

void dummy_client_unbox(unsigned char* buffer, size_t len){

  size_t clen = len - crypto_secretbox_NONCEBYTES;
  unsigned char* nonceptr = &(buffer[clen]);
  if (crypto_secretbox_open_easy(buffer, buffer, clen, nonceptr, rx) != 0){
    printf("DC: unbox failed\n");
  }

  return;
}

int dummy_client_read_reply(unsigned char* data, size_t len){

  dummy_client_unbox(data, len);

  int* replyval = (int*)data;

  printf("DC: enclave said string was %i words\n",*replyval);
  
}
