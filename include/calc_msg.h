#ifndef _CALC_MSG_H_
#define _CALC_MSG_H_


#define CALC_MSG_WORDCOUNT 1
#define CALC_MSG_EXIT 2

typedef struct calc_message_t{
  unsigned short msg_type;
  size_t len;
  char msg[]; // Flexible member
} calc_message_t;


#endif /* _CALC_MSG_H_ */
