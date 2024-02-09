#ifndef ERROR_HEADER_CPP
#define ERROR_HEADER_CPP

#include <cstdio>

#define DEBUG

#ifdef FULL_DEBUG
#define ERROR_MESSAGE(str) (printf("ERROR - %s\n", (str)), 1)
#define SUCCESS_MESSAGE(str) (printf("SUCCESS - %s\n", (str)), 0)
#else
#ifdef DEBUG
#define ERROR_MESSAGE(str) (printf("ERROR - %s\n", (str)), 1)
#define SUCCESS_MESSAGE(str) (0)
#else
#define ERROR_MESSAGE(str) (1)
#define SUCCESS_MESSAGE(str) (0)
#endif
#endif

#endif
