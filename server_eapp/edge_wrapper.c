#include "eapp_utils.h"
#include "string.h"
#include "syscall.h"
#include "edge_wrapper.h"
#include "edge_defines.h"

void edge_init(){
  /* Nothing for now, will probably register buffers/callsites
     later */
}

void ocall_print_value(unsigned long val){

  unsigned long val_ = val;
  ocall(OCALL_PRINT_VALUE, &val_, sizeof(unsigned long), 0, 0);

  return;
}

void ocall_send_report(char* buffer, size_t len){

  ocall(OCALL_SEND_REPORT, buffer, len, 0, 0);

  return;  
}

unsigned long ocall_print_buffer(char* data, size_t data_len){

  unsigned long retval;
  ocall(OCALL_PRINT_BUFFER, data, data_len, &retval ,sizeof(unsigned long));

  return retval;
}

edge_data_t ocall_wait_for_message(){

  edge_data_t msg;
  ocall(OCALL_WAIT_FOR_MESSAGE, NULL, 0, &msg, sizeof(edge_data_t));

  return msg;
}

// TODO failure case
void ocall_wait_for_client_pubkey(unsigned char* pk, size_t len){
  ocall(OCALL_WAIT_FOR_CLIENT_PUBKEY, NULL, 0, pk, len);

  return;
}
