#include "eapp_utils.h"
#include "string.h"
#include "syscall.h"
#include "malloc.h"
#include "eapp_func.h"
#include "ocalls.h"
#include "calculator.h"
#include "sodium.h"
#include "hacks.h"
#include "channel.h"

report get_attestation_report(){
  report ret;
  attest_enclave((void*) (ret.data), server_pk, crypto_kx_PUBLICKEYBYTES);
  return ret;
}

int set_client_pk(pubkey* pk){
  client_pk = (unsigned char*) wait_for_client_pubkey();
  return channel_establish();
}

encl_message_t calc_message(encl_message_t msg){
  calc_message_t* calc_msg = (calc_message_t*) msg.host_ptr;
  size_t wordmsg_len;
    
  if(channel_recv((unsigned char*)calc_msg, msg.len, &wordmsg_len) != 0){
    free(calc_msg);
    continue;
  }

  static encl_message_t reply;
  // free the last message
  if (reply.host_ptr) free(reply.host_ptr);
    	
  if(calc_msg->msg_type == CALC_MSG_EXIT){
    print_buffer("Received exit, exiting\n");
    reply.len = 0;
    reply.host_ptr = NULL;
    return reply;
  }
 
  int val = word_count(calc_msg->msg, wordmsg_len);
  
  free(calc_msg);
  
  reply.len = channel_get_send_size(sizeof(int));
  reply.host_ptr = malloc(reply_size);

  channel_send((unsigned char*)&val, sizeof(int), reply.host_ptr);

  return reply;
}

void register_inverse_functions();

void EAPP_ENTRY eapp_entry(){
  magic_random_init();
  channel_init();

  register_inverse_functions();
  receive_calls(h2ecall_dispatch);

  EAPP_RETURN(0);
}

