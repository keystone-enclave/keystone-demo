#include "calculator.h"


size_t word_count(char* buffer, size_t len){

  char* cur;
  size_t count = 0;
  int prev_whitespace = 1;
  cur = buffer;
  while(*cur != '\0' && len > 0){
    if(	(*cur == ' ' ||
  	 *cur == '\n' ||
  	 *cur == '\t')){
      if( prev_whitespace == 0 ){
  	count++;
  	prev_whitespace = 1;
      }
    }
    else{
      prev_whitespace = 0;
    }
    cur++;
    len--;
  }
  if(prev_whitespace == 0)
    count++;

  return count;
}
