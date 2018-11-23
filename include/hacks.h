#ifndef _HACKS_H_
#define _HACKS_H_

#include "sys/time.h"
#include "poll.h"
#include "sys/stat.h"

/* Why does this file exist?  We are building libsodium into an
 * environment it was not intended to run in, no libc, no fs, no
 * kernel. For demo purposes we are ensuring that we can link
 * libsodium, and that any misuse will result in the enclave
 * exiting. We believe this to be a safe compromise.
 */
#define EAPP_ERR_RET 5
#define BAD_CALL(fn) void fn(void){ocall_print_buffer(#fn,8);EAPP_RETURN(EAPP_ERR_RET);}

int dummy_errno = 0;

BAD_CALL( abort )
BAD_CALL( __assert_fail )
//BAD_CALL( close ) We actually interpose on this, see below
//BAD_CALL( __errno_location ) We actually interpose on this, see below
//BAD_CALL( fcntl ) We actually interpose on this, see below
//BAD_CALL( __fxstat ) We actually interpose on this, see below
//BAD_CALL( __memcpy_chk )
void * __memcpy_chk(void * dest, const void * src, size_t len, size_t destlen) {
  if(destlen < len)
    EAPP_RETURN(EAPP_ERR_RET);
  return memcpy(dest, src, len);
}
//BAD_CALL( open ) We actually interpose on this, see below
//BAD_CALL( poll )
//BAD_CALL( posix_memalign )
int posix_memalign (void **__memptr, size_t __alignment, size_t __size) {EAPP_RETURN(EAPP_ERR_RET); return 0;};
BAD_CALL( raise )
//BAD_CALL( read ) We actually interpose on this, see below
BAD_CALL( syscall )
//BAD_CALL( sysconf )  We actually interpose on this, see below
//BAD_CALL( getpid ) We actually interpose on this, see below
//BAD_CALL( gettimeofday ) We actually interpose on this, see below


/* We are going to make a small seed amount of entropy available for
 * libsodium's stuff. After that we refuse and shutdown.
 */

#define MAGIC_RANDOM_FD 55

int random_is_open = 0;
size_t remaining_bytes;
unsigned char* entropy_bytes;


void magic_random_init(){
  ocall_print_buffer("NOT USING REAL RANDOMNESS: TEST ONLY\n",37);
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

int open(const char* path, int flags){
  if( random_is_open ){
    return -1;
  }

  /* "open" random for them */
  random_is_open = 1;
  return MAGIC_RANDOM_FD;
}

ssize_t read(int fd, void* buf, size_t count){
  if(fd != MAGIC_RANDOM_FD){
    return 0;
  }
  
  unsigned char* _buf = (unsigned char*) buf;
  size_t done = 0;
  while( remaining_bytes > 0  && done < count){
    _buf[done] = *entropy_bytes;
    entropy_bytes++;
    remaining_bytes--;
    done++;
  }
  return done;
}

int close(int fd){
  if(fd != MAGIC_RANDOM_FD){
    return -1;
  }
  random_is_open = 0;
  return 0;
}

int getpid(){
  return 10;
}

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
int poll (struct pollfd *__fds, nfds_t __nfds, int __timeout){
  return POLLIN;
}

int __fxstat (int vers, int fd, struct stat *buf)
{
  if( fd != MAGIC_RANDOM_FD ){
    return -1;
  }

  /* Our random device is a character device */
  
  buf->st_mode |= S_IFCHR;

  return 0;
}

int fcntl(int fd, int cmd, ... /* arg */ ){
  if( fd != MAGIC_RANDOM_FD ){
    return -1;
  }

  return 0;
  
}

#define _SC_PAGESIZE 30
#define RISCV_PAGESIZE 4096

long sysconf(int name){
  if(name == _SC_PAGESIZE){
    return RISCV_PAGESIZE;
  }
  return -1;
}

#endif /* _HACKS_H_ */
