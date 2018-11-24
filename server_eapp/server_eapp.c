#include "eapp_utils.h"
#include "string.h"
#include "syscall.h"
#include "malloc.h"
#include "edge_wrapper.h"
#include "calculator.h"
#include "sodium.h"
#include "hacks.h"
#include "channel.h"

void EAPP_ENTRY eapp_entry(){

  char* outstr = "Enclave running!\n";
  
  edge_init();

  unsigned long ret = ocall_print_buffer(outstr, 17);

  magic_random_init();

  channel_init();

  // TODO sizeof report
  char buffer[2048];

  attest_enclave((void*) buffer, server_pk, crypto_kx_PUBLICKEYBYTES);

  ocall_send_report(buffer, 2048);

  ocall_wait_for_client_pubkey(client_pk, crypto_kx_PUBLICKEYBYTES);

  channel_establish();
  
  //  while(1){
    edge_data_t msg = ocall_wait_for_message();
    calc_message_t* calc_msg = malloc(msg.size);

    if(calc_msg == NULL){
      ocall_print_value(0);
      EAPP_RETURN(ret);
    }
    copy_from_shared(calc_msg, msg.offset, msg.size);

    // TODO handle failure
    channel_recv((unsigned char*)calc_msg, msg.size);
    
    if(calc_msg->msg_type == CALC_MSG_EXIT){
      ocall_print_buffer("GOT EXIT\n",9);
      EAPP_RETURN(ret);
    }
    // TODO safety check on len
    int val = word_count(calc_msg->msg);

    // TODO free memory
    size_t reply_size =channel_get_send_size(sizeof(int));
    unsigned char* reply_buffer = malloc(reply_size);
    channel_send((unsigned char*)&val, sizeof(int), reply_buffer);
    ocall_send_reply(reply_buffer,reply_size);
    
    free(calc_msg);
    //  }
  
  EAPP_RETURN(ret);
}
