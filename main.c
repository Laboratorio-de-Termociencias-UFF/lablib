#include "src/structure/include/pointer.h"

int main(){
    printf("Test Nullity:\n");
    Pointer ptr = pointer_null();
    printf("Ptr - %p, %p, %d\n", ptr.pHost, ptr.pDev, ptr.type);
    printf("Test Allocation:\n");
    pointer_alloc_linked(&ptr,10);
    printf("Ptr - %p, %p, %d\n", ptr.pHost, ptr.pDev, ptr.type);
    printf("Test Free:\n");
    pointer_free_linked(&ptr);
    printf("Ptr - %p, %p, %d\n", ptr.pHost, ptr.pDev, ptr.type);

    return 0;
}