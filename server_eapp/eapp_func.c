#include "eapp_func.h"

int strcmp(const char *s1, const char *s2)
{
        while (*s1 == *s2++)
                if (*s1++ == 0)
                        return (0);
        return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}

int strncmp(const char *s1, const char *s2, unsigned long long n)
{

        if (n == 0)
                return (0);
        do {
                if (*s1 != *s2++)
                        return (*(const unsigned char *)s1 -
                                *(const unsigned char *)(s2 - 1));
                if (*s1++ == 0)
                        break;
        } while (--n != 0);
        return (0);
}

void __assert_fail(const char *assertion,
              const char *file,
              unsigned int line,
              const char *function)
{
	EAPP_RETURN(1);
}

void* memchr(const void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char*)s;
    while( n-- )
        if( *p != (unsigned char)c )
            p++;
        else
            return p;
    return 0;
}

