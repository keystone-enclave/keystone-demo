#include "calculator.h"


size_t word_count(char* buffer){

  char* cur;
  size_t count = 0;
  int prev_whitespace = 1;
  cur = buffer;
  while(*cur != '\0'){
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
  }
  if(prev_whitespace == 0)
    count++;

  return count;
}
