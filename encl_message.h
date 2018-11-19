#ifndef _ENCL_MESSAGE_H_
#define _ENCL_MESSAGE_H_
#include "edge_common.h"

typedef unsigned char byte;

typedef struct report_t {
  byte sm_hash[64];
  byte sm_pubkey[32];
  byte sm_signature[64];
  byte encl_hash[64];
  uint64_t encl_data_len;
  byte encl_data[1024];
  byte encl_signature[64];
} report_t;

typedef struct network_message_t {
  size_t data_len;
  edge_data_offset offset;
} network_message_t;

typedef struct data_message_t {
  unsigned int msg_type;

  size_t data_len;
  
  unsigned char data[];
  
} edge_data_message_t;

#endif /* _ENCL_MESSAGE_H_ */
