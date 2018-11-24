#include "eapp_utils.h"
#include "sodium.h"
#include "channel.h"
#include "string.h"
#include "edge_wrapper.h"

void channel_init(){

  /* libsodium config */
  randombytes_set_implementation(&randombytes_salsa20_implementation);

  if(sodium_init() < 0 ){
    EAPP_RETURN(1);
  }

  /* Generate our keys */
  if(crypto_kx_keypair(server_pk, server_sk) != 0){
    ocall_print_buffer("Keygen1 failed\n",16);
    EAPP_RETURN(1);
  }

}

void channel_establish(){

  /* Ask libsodium to generate session keys based on the recv'd pk */

  if(crypto_kx_server_session_keys(rx, tx, server_pk, server_sk, client_pk) != 0) {
    ocall_print_buffer("Keygen2 failed\n",16);
    EAPP_RETURN(1);
  }

}

int channel_recv(unsigned char* msg_buffer, size_t len){
  /* We store the nonce at the end of the ciphertext buffer for easy
     access */
  size_t clen = len - crypto_secretbox_NONCEBYTES;
  unsigned char* nonceptr = &(msg_buffer[clen]);

  if (crypto_secretbox_open_easy(msg_buffer, msg_buffer, clen, nonceptr, rx) != 0){
    //TODO: Drop message
    ocall_print_buffer("BAD MSG\n",9);
    return -1;
  }

  return 0;
}

size_t channel_get_send_size(size_t len){
  return crypto_secretbox_MACBYTES + len + crypto_secretbox_NONCEBYTES;
}

void channel_send(unsigned char* msg, size_t len, unsigned char* ctx){
  /* We store the nonce at the end of the ciphertext buffer for easy
     access */
  unsigned char* nonceptr = &(ctx[crypto_secretbox_MACBYTES+len]);
  randombytes_buf(nonceptr, crypto_secretbox_NONCEBYTES);
  
  if(crypto_secretbox_easy(ctx, msg, len, nonceptr, tx) != 0){
    ocall_print_buffer("Channel2 failed\n",17);
    EAPP_RETURN(1);
  }

}
