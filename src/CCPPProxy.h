#pragma once


constexpr unsigned char bridge[] = {                    //push   rsi
    0x48, 0xb8, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11,  // movabs rax,0x1122334455667788
    
    0x4c, 0x8b, 0x78, 0x08,            // mov    r15,QWORD PTR [rax+0x8]
    0xff, 0x10,                  // call   QWORD PTR [rax]
    0xc3                      //ret 
    };

class C1;

template<typename ReturnType, typename ...FunctionArgumensts>
struct CCPPProxy{
    template<  ReturnType (C1::*function_ptr)(FunctionArgumensts ...args)>
    static ReturnType call(FunctionArgumensts ...args){
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
    
    return (pC1->*function_ptr)(args...);
    }

   

};
