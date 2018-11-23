
#include "dummy_client.h"

unsigned char pubkey[32];

void* dummy_client_pubkey(){
  printf("USING DUMMY PUBKEY\n");
  

  return (void*)pubkey;
}

const char* longstr = "hello hello hello hello hello hello hello hello hello hello";

void* dummy_client_generate_message(size_t* len){
  /* This all will happen on the remote */
  size_t datalen = strlen(longstr)+1; 
  calc_message_t* calc_msg = (calc_message_t*)malloc(sizeof(calc_message_t) + datalen);
  calc_msg->msg_type = CALC_MSG_WORDCOUNT;
  calc_msg->len = datalen;
  memcpy(calc_msg->msg, (void*)longstr, calc_msg->len);
  size_t totalsize = calc_msg->len + sizeof(calc_message_t);

  *len = totalsize;

  return (void*)calc_msg;
  
  
}

int dummy_client_read_reply(){
  
}
