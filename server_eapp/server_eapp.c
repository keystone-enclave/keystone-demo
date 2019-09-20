#include "eapp_utils.h"
#include "string.h"
#include "syscall.h"
#include "malloc.h"
#include "eapp_func.h"
#include "ocalls_eapp.h"
#include "calculator.h"
#include "sodium.h"
#include "hacks.h"
#include "channel.h"

void attest_and_establish_channel(){
  // TODO sizeof report
  char buffer[2048];
  attest_enclave((void*) buffer, server_pk, crypto_kx_PUBLICKEYBYTES);
  send_report(buffer, 2048);


  client_pk = (unsigned char*) wait_for_client_pubkey();
  channel_establish();
}

void handle_messages(){
  encl_message_t msg;
  while(1){
    msg = wait_for_message();
    calc_message_t* calc_msg = (calc_message_t*) msg.host_ptr;
	size_t wordmsg_len;
    
    if(channel_recv((unsigned char*)calc_msg, msg.len, &wordmsg_len) != 0){
      free(calc_msg);
      continue;
    }
    	
    if(calc_msg->msg_type == CALC_MSG_EXIT){
      print_buffer("Received exit, exiting\n");
      EAPP_RETURN(0);
    }

    int val = word_count(calc_msg->msg, wordmsg_len);

    // Done with the message, free it
    free(calc_msg);

    size_t reply_size =channel_get_send_size(sizeof(int));
    unsigned char* reply_buffer = malloc(reply_size);
    if(reply_buffer == NULL){
      print_buffer("Reply too large to allocate, no reply sent\n");
      continue;
    }

    channel_send((unsigned char*)&val, sizeof(int), reply_buffer);
    send_reply(reply_buffer,reply_size);

    free(reply_buffer);

  }

}

void EAPP_ENTRY eapp_entry(){

//  edge_init();
  magic_random_init();
  channel_init();

  attest_and_establish_channel();
  handle_messages();

  EAPP_RETURN(0);
}
