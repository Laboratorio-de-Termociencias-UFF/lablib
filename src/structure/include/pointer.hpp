#ifndef POINTER_HEADER_CPP
#define POINTER_HEADER_CPP

#include <cstdlib>
#include "cuda_runtime.h"

#include "../../error/include/error.hpp"

#define DEFAULT_POINTER_TYPE LINKED_POINTER

enum PointerType
{
    NULL_POINTER = 0,
    CPU_POINTER = 1,
    GPU_POINTER = 2,
    LINKED_POINTER = 3
};

struct Pointer
{
private:
    void *pHost;
    void *pDev;
    PointerType mType;

protected:
public:
    Pointer()
    {
        pHost = NULL;
        pDev = NULL;
        mType = NULL_POINTER;
    }

    template <typename T>
    inline T *host()
    {
        return (T *)pHost;
    }
    template <typename T>
    inline T *dev()
    {
        return (T *)pDev;
    }

    int alloc(unsigned size, PointerType type)
    {
        switch (type)
        {
        case PointerType::NULL_POINTER:
            return ERROR_MESSAGE("NULL Allocation");
            break;
        case PointerType::CPU_POINTER:
            if (mType & CPU_POINTER)
            {
                return ERROR_MESSAGE("CPU Allocation");
            }
            mType = (PointerType)(mType | CPU_POINTER);
            pHost = std::malloc(size);
            if (pHost == NULL)
            {
                return ERROR_MESSAGE("CPU Allocation - malloc");
            }
            break;
        case PointerType::GPU_POINTER:
            if (mType & GPU_POINTER)
            {
                return ERROR_MESSAGE("GPU Allocation");
            }
            mType = (PointerType)(mType | GPU_POINTER);
            cudaMalloc(&pDev, size);
            break;
        case PointerType::LINKED_POINTER:
            if (mType != NULL_POINTER)
            {
                return ERROR_MESSAGE("Linked Allocation");
            }
            mType = LINKED_POINTER;
            pHost = malloc(size);
            if (pHost == NULL)
            {
                return ERROR_MESSAGE("Linked Allocation - malloc");
            }
            cudaMalloc(&pDev, size);
            break;
        default:
            break;
        }
        return 0;
    }

    int free(PointerType type)
    {
        switch (type)
        {
        case PointerType::NULL_POINTER:
            ERROR_MESSAGE("NULL Free");
            break;
        case PointerType::CPU_POINTER:
            if (!(mType & CPU_POINTER))
            {
                return ERROR_MESSAGE("CPU Free");
            }
            type = (PointerType)(type & !CPU_POINTER);
            std::free(pHost);
            break;
        case PointerType::GPU_POINTER:
            if (!(mType & GPU_POINTER))
            {
                return ERROR_MESSAGE("GPU Free");
            }
            type = (PointerType)(type & !GPU_POINTER);
            cudaFree(pDev);
            break;
        case PointerType::LINKED_POINTER:
            if (mType != LINKED_POINTER)
            {
                return ERROR_MESSAGE("Linked Free");
            }
            type = NULL_POINTER;
            std::free(pHost);
            cudaFree(pDev);
            break;
        default:
            break;
        }
        return 0;
    }
};

#endif