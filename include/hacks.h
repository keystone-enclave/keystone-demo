#ifndef _HACKS_H_
#define _HACKS_H_

#include "sys/time.h"
#include <stdarg.h>

/* Why does this file exist?  We are building libsodium into an
 * environment it was not intended to run in, no libc, no fs, no
 * kernel. For demo purposes we are ensuring that we can link
 * libsodium, and that any misuse will result in the enclave
 * exiting. We believe this to be a safe compromise.
 *
 * This only provides a few functions, and a syscall impl that handles
 * getrandom only.
 */
#define EAPP_ERR_RET 5
#define BAD_CALL(fn) void fn(void){ocall_print_buffer(#fn);EAPP_RETURN(EAPP_ERR_RET);}

int dummy_errno = 0;

BAD_CALL( abort )
BAD_CALL( __assert_fail )
BAD_CALL( close )
//BAD_CALL( __errno_location ) We actually interpose on this, see below
BAD_CALL( fcntl )
BAD_CALL( __fxstat )
//BAD_CALL( __memcpy_chk )
void * __memcpy_chk(void * dest, const void * src, size_t len, size_t destlen) {
  if(destlen < len)
    EAPP_RETURN(EAPP_ERR_RET);
  return memcpy(dest, src, len);
}
BAD_CALL( open )
BAD_CALL( poll )
//BAD_CALL( posix_memalign )
int posix_memalign (void **__memptr, size_t __alignment, size_t __size) {EAPP_RETURN(EAPP_ERR_RET); return 0;};
BAD_CALL( raise )
BAD_CALL( read )
//BAD_CALL( syscall )  We actually interpose on this, see below
//BAD_CALL( sysconf )  We actually interpose on this, see below
//BAD_CALL( getpid ) We actually interpose on this, see below
//BAD_CALL( gettimeofday ) We actually interpose on this, see below


/* We are going to make a small seed amount of entropy available for
 * libsodium's stuff. After that we refuse and shutdown.
 */

size_t remaining_bytes;
unsigned char* entropy_bytes;

void magic_random_init(){
  ocall_print_buffer("NOT USING REAL RANDOMNESS: TEST ONLY\n");
  entropy_bytes = (unsigned char*)malloc(512);
  if(!entropy_bytes){
    EAPP_RETURN(EAPP_ERR_RET);
  }
  int i;
  for(i=0;i<512;i++){
    entropy_bytes[i] = i%255;
  }
  remaining_bytes = 512;
}

/* TODO give it a pid */
int getpid(){
  return 10;
}

/* TODO give a better timeofday */
int gettimeofday(struct timeval *tv, struct timezone *tz){
  /* We will just return cycle count for now */
  unsigned long cycles;
  asm volatile ("rdcycle %0" : "=r" (cycles));

  tv->tv_sec = cycles;
  tv->tv_sec = cycles;

  return 0;
}

int* __errno_location(void){
  return &dummy_errno;
}

#define _SC_PAGESIZE 30
#define RISCV_PAGESIZE 4096

long sysconf(int name){
  if(name == _SC_PAGESIZE){
    return RISCV_PAGESIZE;
  }
  return -1;
}

#define SYS_getrandom 278

long syscall(long number, ...){
  /* We only handle one 'syscall' from libc, getrandom */
  if(number != SYS_getrandom){
    return -1;
  }

  va_list args;
  va_start(args, number);

  char* buffer = va_arg(args, char*);
  size_t count = va_arg(args, size_t);
  //int flags = va_arg(args, int); We don't use flags

  unsigned char* _buf = (unsigned char*) buffer;
  size_t done = 0;
  while( remaining_bytes > 0  && done < count){
    _buf[done] = *entropy_bytes;
    entropy_bytes++;
    remaining_bytes--;
    done++;
  }
  return done;

}

#endif /* _HACKS_H_ */
