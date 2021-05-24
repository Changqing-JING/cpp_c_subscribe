#pragma once
#include "CPUAdapter.h"


template<typename ClassName, typename ReturnType, typename ...FunctionArgumensts>
struct ClassMemberFuctionBind{
    /*
        This Function uses r15 register on x86_64 to pass argument with assembly code in bridge.
        Every .cpp file which includes this header file must be compiled with argument -ffixed-r15, otherwise the r15 register maybe get corrupt.
    */
    template<  ReturnType (ClassName::*function_ptr)(FunctionArgumensts ...args)>
    static ReturnType call(FunctionArgumensts ...args){
    void* pointer;;

    #ifdef __GNUC__
        #ifdef x64
            __asm__(
                "mov %%r15, %0":"=r"(pointer)
            );
        #elif arm64
            __asm__(
                "mov x15, %0":"=r"(pointer)
            );
        #endif
    #elif defined _MSC_VER && defined __clang__
        #ifdef x64
            __asm {mov[pointer], r15 }
        #elif arm64
            __asm__(
                "mov x15, %0":"=r"(pointer)
            );
        #endif
    #else
        #error "unsupported compiler"
    #endif
    
    return (((ClassName*)pointer)->*function_ptr)(args...);
    }

   

};
