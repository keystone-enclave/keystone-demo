#include <string.h>
#include "trusted_client.h"
#include "client.h"

#include "test_dev_key.h"
#include "enclave_expected_hash.h"
#include "sm_expected_hash.h"

unsigned char client_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char client_sk[crypto_kx_SECRETKEYBYTES];
unsigned char server_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char rx[crypto_kx_SESSIONKEYBYTES];
unsigned char tx[crypto_kx_SESSIONKEYBYTES];

int double_fault;
int channel_ready;

void trusted_client_exit(){
  if(double_fault || !channel_ready){
    printf("DC: Fatal error, exiting. Remote not cleanly shut down.\n");
    exit(-1);
  }
  else{
    double_fault = 1;
    printf("[TC] Exiting. Attempting clean remote shutdown.\n");
    send_exit_message();
    exit(0);
  }
}

void trusted_client_init(){

  if( sodium_init() != 0){
    printf("[TC] Libsodium init failure\n");
    trusted_client_exit();
  }
  if( crypto_kx_keypair(client_pk,client_sk) != 0){
    printf("[TC] Libsodium keypair gen failure\n");
    trusted_client_exit();
  }

  channel_ready = 0;
}

byte* trusted_client_pubkey(size_t* len){
  *len = crypto_kx_PUBLICKEYBYTES;
  return (byte*)client_pk;
}

void trusted_client_get_report(void* buffer){

  Report report;
  report.fromBytes((unsigned char*)buffer);
  report.printJson();

  if (report.verify(enclave_expected_hash,
		    sm_expected_hash,
		    _sanctum_dev_public_key))
  {
    printf("[TC]Attestation signature and enclave hash are valid\n");
  }
  else
  {
    printf("[TC]Attestation report is NOT valid\n");
    trusted_client_exit();
  }

  if(report.getDataSize() !=  crypto_kx_PUBLICKEYBYTES){
    printf("[TC] Bad report data sec size\n");
    trusted_client_exit();
  }

  memcpy(server_pk, report.getDataSection(), crypto_kx_PUBLICKEYBYTES);

  if(crypto_kx_client_session_keys(rx, tx, client_pk, client_sk, server_pk) != 0) {
    printf("[TC] Bad session keygen\n");
    trusted_client_exit();
  }
  
  printf("[TC] Keygen stage done\n");
  channel_ready = 1;
}

byte* trusted_client_box(byte* msg, size_t size, size_t* finalsize){

  *finalsize = size + crypto_secretbox_MACBYTES + crypto_secretbox_NONCEBYTES;
  byte* buffer = (byte*)malloc(*finalsize);
  if(buffer == NULL){
    printf("[TC] NOMEM for msg\n");
    trusted_client_exit();
  }

  memcpy(buffer, msg, size);
  unsigned char* nonceptr = &(buffer[crypto_secretbox_MACBYTES+size]);
  randombytes_buf(nonceptr, crypto_secretbox_NONCEBYTES);

  if(crypto_secretbox_easy(buffer, buffer, size, nonceptr, tx) != 0){
    printf("[TC] secretbox failed\n");
    trusted_client_exit();
  }

  return(buffer);
}

void trusted_client_unbox(unsigned char* buffer, size_t len){

  size_t clen = len - crypto_secretbox_NONCEBYTES;
  unsigned char* nonceptr = &(buffer[clen]);
  if (crypto_secretbox_open_easy(buffer, buffer, clen, nonceptr, rx) != 0){
    printf("[TC] unbox failed\n");
    trusted_client_exit();
  }
  return;
}

int trusted_client_read_reply(unsigned char* data, size_t len){

  trusted_client_unbox(data, len);

  int* replyval = (int*)data;

  printf("[TC] enclave said string was %i words long\n",*replyval);
  
}

void send_exit_message(){

  size_t pt_size;
  calc_message_t* pt_msg = generate_exit_message(&pt_size);

  size_t ct_size;
  byte* ct_msg = trusted_client_box((byte*)pt_msg, pt_size, &ct_size);

  send_buffer(ct_msg, ct_size);

  free(pt_msg);
  free(ct_msg);
}

void send_wc_message(char* buffer){

  size_t pt_size;
  calc_message_t* pt_msg = generate_wc_message(buffer, strlen(buffer)+1, &pt_size);

  size_t ct_size;
  byte* ct_msg = trusted_client_box((byte*)pt_msg, pt_size, &ct_size);

  send_buffer(ct_msg, ct_size);

  free(pt_msg);
  free(ct_msg);

}

calc_message_t* generate_wc_message(char* buffer, size_t buffer_len, size_t* finalsize){
  calc_message_t* message_buffer = (calc_message_t*)malloc(buffer_len+sizeof(calc_message_t));
  
  message_buffer->msg_type = CALC_MSG_WORDCOUNT;
  message_buffer->len = buffer_len;
  memcpy(message_buffer->msg, buffer, buffer_len);

  *finalsize = buffer_len + sizeof(calc_message_t);
  
  return message_buffer;
};

calc_message_t* generate_exit_message(size_t* finalsize){

  calc_message_t* message_buffer = (calc_message_t*)malloc(sizeof(calc_message_t));
  message_buffer->msg_type = CALC_MSG_EXIT;
  message_buffer->len = 0;

  *finalsize = sizeof(calc_message_t);

  return message_buffer;
  
}
