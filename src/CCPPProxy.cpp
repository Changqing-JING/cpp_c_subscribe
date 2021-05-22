#include "C1.h"

void CCPPProxy(int num){
    C1* pC1;;

    #ifdef __GNUC__
        __asm__(
            "mov %%r15, %0":"=r"(pC1)
        );
    #elif defined _MSC_VER && defined __clang__
        __asm {mov[pC1], r15 }
    #else
        #error "unsupported compiler"
    #endif
    
    pC1->sub_foo(num);
}