#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "stddef.h"

#define CALC_MSG_WORDCOUNT 1
#define CALC_MSG_EXIT 2

typedef struct calc_message_t{
  unsigned short msg_type;
  size_t len;
} calc_message_t;

size_t word_count(char* buffer);


#endif /* _CALCULATOR_H_ */
