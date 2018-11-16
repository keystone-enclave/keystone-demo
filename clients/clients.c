#include "eapp_utils.h"
#include "string.h"
#include "syscall.h"
#include "malloc.h"
#include "edge_wrapper.h"

void EAPP_ENTRY eapp_entry(){

  char* outstr = "Enclave running!\n";
  
  edge_init();
  
  unsigned long ret = ocall_print_buffer(outstr, 17);

  edge_data_t msg = ocall_wait_for_message();
  
  void* msg_data = malloc(msg.len);

  if(msg_data == NULL){
    ocall_print_value(0);
    EAPP_RETURN(ret);
  }
  
  copy_from_shared(msg_data, msg.offset, msg.len);

  ocall_print_value(msg.len);
  
  EAPP_RETURN(ret);
}
