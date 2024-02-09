#include "../include/pointer.h"

int pointer_alloc_cpu(Pointer *pointer, long int size)
{
    if (pointer->type & CPU_POINTER)
    {
        return ERROR_MESSAGE("CPU Allocation");
    }
    pointer->type = (enum PointerType)(pointer->type | CPU_POINTER);
    pointer->pHost = malloc(size);
    if (pointer->pHost == NULL)
    {
        return ERROR_MESSAGE("CPU Allocation - malloc");
    }
    return SUCCESS_MESSAGE("CPU Allocation");
}

int pointer_alloc_gpu(Pointer *pointer, long int size)
{
    if (pointer->type & GPU_POINTER)
    {
        return ERROR_MESSAGE("GPU Allocation");
    }
    pointer->type = (enum PointerType)(pointer->type | GPU_POINTER);
    cudaMalloc(&(pointer->pDev), size);
    return SUCCESS_MESSAGE("GPU Allocation");
}

int pointer_alloc_linked(Pointer *pointer, long int size)
{
    if (pointer->type != NULL_POINTER)
    {
        return ERROR_MESSAGE("Linked Allocation");
    }
    pointer->type = LINKED_POINTER;
    pointer->pHost = malloc(size);
    if (pointer->pHost == NULL)
    {
        return ERROR_MESSAGE("Linked Allocation - malloc");
    }
    cudaMalloc(&(pointer->pDev), size);
    return SUCCESS_MESSAGE("Linked Allocation");
}

int pointer_free_cpu(Pointer *pointer)
{
    if (!(pointer->type & CPU_POINTER))
    {
        return ERROR_MESSAGE("CPU Free");
    }
    pointer->type = (enum PointerType)(pointer->type & !CPU_POINTER);
    free(pointer->pHost);
    pointer->pHost = NULL;
    return SUCCESS_MESSAGE("CPU Free");
}

int pointer_free_gpu(Pointer *pointer)
{
    if (!(pointer->type & GPU_POINTER))
    {
        return ERROR_MESSAGE("GPU Free");
    }
    pointer->type = (enum PointerType)(pointer->type & !GPU_POINTER);
    cudaFree(pointer->pDev);
    pointer->pDev = NULL;
    return SUCCESS_MESSAGE("GPU Free");
}

int pointer_free_linked(Pointer *pointer)
{
    if (pointer->type != LINKED_POINTER)
    {
        return ERROR_MESSAGE("Linked Free");
    }
    pointer->type = NULL_POINTER;
    free(pointer->pHost);
    cudaFree(pointer->pDev);
    pointer->pHost = NULL;
    pointer->pDev = NULL;
    return SUCCESS_MESSAGE("Linked Free");
}