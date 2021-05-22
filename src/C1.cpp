#include <cstdio>
#include <cstdint>
#include <cstring>


#include "C1.h"
#include "MemoryUtils.hpp"
#include "CCPPProxy.h"



constexpr unsigned char bridge[] = {                    //push   rsi
     0x48, 0xb8, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11,  // movabs rax,0x1122334455667788
      
    0x48, 0x8b, 0x10,                //mov    rdx,QWORD PTR [rax]
    0x4c, 0x8b, 0x78, 0x08,            // mov    r15,QWORD PTR [rax+0x8]
    0xff, 0xd2,                  // call   rdx
    0xc3                      //ret 
     };


C1::C1(int a)
    {
            this->a = a;
            gerertion_function();
    }

C1::~C1(){
     
            freeAlignedMemroy((void*)this->tf);
      
}


void C1::sub_foo(int input){
            int result = this->a + input;
            printf("result is %d\n", result);
        }

void C1::subscribe_to_c_lib(){
    
    subscribe(this->tf);

}

void C1::gerertion_function(){
            this->tf = (TF)allocExecutableMemory(4096);
            memcpy((void*)this->tf, bridge, sizeof(bridge));
            char* address_holder = (char*)this->tf + 2;
            *((uintptr_t*)address_holder) = (uintptr_t)this->abi_area;

            abi_area[0] = (void*)&CCPPProxy;
            abi_area[1] = this;          
}