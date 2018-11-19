#include "eapp_utils.h"
#include "string.h"
#include "syscall.h"
#include "malloc.h"
#include "edge_wrapper.h"
#include "calculator.h"

void EAPP_ENTRY eapp_entry(){

  char* outstr = "Enclave running!\n";
  
  edge_init();
  
  unsigned long ret = ocall_print_buffer(outstr, 17);


  //  while(1){
    edge_data_t msg = ocall_wait_for_message();
    void* msg_data = malloc(msg.size);

    if(msg_data == NULL){
      ocall_print_value(0);
      EAPP_RETURN(ret);
    }
    copy_from_shared(msg_data, msg.offset, msg.size);
	
    /* TODO Channel stuff here */

    if(((calc_message_t*)msg_data)->msg_type == CALC_MSG_EXIT){
      ocall_print_buffer("GOT EXIT\n",9);
      EAPP_RETURN(ret);
    }
    char* word_data = msg_data + sizeof(calc_message_t);
    int val = word_count(word_data);
    ocall_print_value(val);
    
    free(msg_data);
    //  }
  
  EAPP_RETURN(ret);
}
