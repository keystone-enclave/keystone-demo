#include <stdint.h>
#include <stddef.h>
#include "edge_wrapper.h"
#include "eapp_utils.h"

void EAPP_ENTRY eapp_entry(){

  char* msg = "hello world!\n";
  char* msg2 = "2nd hello world!\n";
  
  edge_init();
  
  unsigned long ret = ocall_print_buffer(msg, 13);
  ocall_print_buffer(msg2, 17);

  ocall_print_value(ret);
  
  EAPP_RETURN(ret);
}
