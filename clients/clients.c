#include "eapp_utils.h"
#include "string.h"
#include "syscall.h"
#include "malloc.h"
#include "edge_wrapper.h"
#include "calculator.h"
#include "sodium.h"
#include "hacks.h"

void EAPP_ENTRY eapp_entry(){

  char* outstr = "Enclave running!\n";
  
  edge_init();

  unsigned long ret = ocall_print_buffer(outstr, 17);

  magic_random_init();
  
  /* libsodium config */
  randombytes_set_implementation(&randombytes_salsa20_implementation);

  if(sodium_init() < 0 ){
    EAPP_RETURN(1);
  }

  //  while(1){
    edge_data_t msg = ocall_wait_for_message();
    calc_message_t* calc_msg = malloc(msg.size);

    if(calc_msg == NULL){
      ocall_print_value(0);
      EAPP_RETURN(ret);
    }
    copy_from_shared(calc_msg, msg.offset, msg.size);
	
    /* TODO Channel stuff here */

    if(calc_msg->msg_type == CALC_MSG_EXIT){
      ocall_print_buffer("GOT EXIT\n",9);
      EAPP_RETURN(ret);
    }
    // TODO safety check on len
    int val = word_count(calc_msg->msg);

    // TODO send a reply message
    ocall_print_value(val);
    
    free(calc_msg);
    //  }
  
  EAPP_RETURN(ret);
}
