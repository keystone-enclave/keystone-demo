#ifndef _ENCL_MESSAGE_H_
#define _ENCL_MESSAGE_H_
#include "edge_common.h"
#include "report.h"
typedef unsigned char byte;

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
