#include <cstdio>
#include <cstdint>
#include <cstring>


#include "C1.h"
#include "MemoryUtils.hpp"
#include "CCPPProxy.h"






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

            abi_area[0] = (void*)&(CCPPProxy<void, int>::call<&C1::sub_foo>);
            abi_area[1] = this;          
}