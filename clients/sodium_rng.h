#ifndef _SODIUM_RNG_H_
#define _SODIUM_RNG_H_
typedef struct randombytes_implementation {
  const char *(*implementation_name)(void);
  uint32_t    (*random)(void);
  void        (*stir)(void);
  uint32_t    (*uniform)(const uint32_t upper_bound);
  void        (*buf)(void * const buf, const size_t size);
  int         (*close)(void);
} randombytes_implementation;

const char* name = "dummy_impl";

const char* dummy_impl_name(void){
  return name;
}

uint32_t dummy_impl_random(void){
  return 4;
}

void dummy_impl_stir(void){}

uint32_t dummy_impl_uniform(const uint32_t upper_bound){
  return 5;
}

void dummy_impl_buf(void* const buf, const size_t size){
  size_t i;
  for(i = 0; i < size
}

int dummy_impl_close(void){
  return 0;
}

#endif /* _SODIUM_RNG_H_ */
