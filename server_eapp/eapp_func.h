#ifndef __EAPP_FUNC_H
#define __EAPP_FUNC_H

#include "eapp_utils.h"
#include "edge_call.h"
#include <syscall.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, unsigned long long n);

void __assert_fail(const char *assertion,
              const char *file,
              unsigned int line,
              const char *function);

void* memchr(const void *s, int c, size_t n);

#endif
