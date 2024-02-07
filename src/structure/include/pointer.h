#ifndef POINTER_HEADER_C
#define POINTER_HEADER_C

#include "stdio.h"
#include "stdlib.h"
#include "cuda_runtime.h"

#define SUCCESS_MESSAGE 0
#define ERROR_MESSAGE(str) (printf("ERROR - %s", (str)), 1)
#define DEFAULT_POINTER_TYPE LINKED_POINTER

enum PointerType
{
    NULL_POINTER = 0,
    CPU_POINTER = 1,
    GPU_POINTER = 2,
    LINKED_POINTER = 3
};

typedef struct
{
    void *pHost;
    void *pDev;
    enum PointerType type;
} Pointer;

inline Pointer pointer_null() { return (Pointer){NULL, NULL, NULL_POINTER}; };

int pointer_alloc_cpu(Pointer *pointer, long int size);
int pointer_alloc_gpu(Pointer *pointer, long int size);
int pointer_alloc_linked(Pointer *pointer, long int size);

int pointer_free_cpu(Pointer *pointer, long int size);
int pointer_free_gpu(Pointer *pointer, long int size);
int pointer_free_linked(Pointer *pointer, long int size);

#endif