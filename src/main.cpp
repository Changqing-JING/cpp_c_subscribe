#include <cstdio>
#include <cstdint>
#include <cstring>
#include "MemoryUtils.hpp"

extern "C"{
    #include "lib.h"
}

#if ! __unix__

#error "Unsupported OS"

#endif

void subscribe_proxy(int num, void* p);

unsigned char bridge[] = {   0x53 ,                     //push   rbx
     0x48, 0xb8, 0x88, 0x77, 0x66, 0x55, 0x44,   // movabs rax,0x1223334455667788
      0x33, 0x23, 0x12,
      0x48, 0x8b, 0x18,                //mov    rbx,QWORD PTR [rax]
      0x48, 0x83, 0xc0, 0x08,             //add    rax,0x8
     0x48, 0x8b, 0x30,               // mov    rsi,QWORD PTR [rax]
     0xff, 0xd3,                  // call   rbx
     0x5b,                      //pop    rbx
     0xc3                      //ret 
     };

class C1{
    public:
        C1(int a){
            this->a = a;
            gerertion_function();
        }

        ~C1(){
            freeAlignedMemroy((void*)this->tf);
        }

        void sub_foo(int input){
            int result = this->a + input;
            printf("result is %d\n", result);
        }

        void subscribe_to_c_lib(){
            
            subscribe(this->tf);

        }

        
    private:
        unsigned char abi_area[2*sizeof(void*)];

        void gerertion_function(){
            this->tf = (TF)allocExecutableMemory(4096);
            memcpy((void*)this->tf, bridge, sizeof(bridge));
            char* address_holder = (char*)this->tf + 3;
            *((uintptr_t*)address_holder) = (uintptr_t)this->abi_area;

            void* func_ptr = (void*)&subscribe_proxy;
            void* address_for_func = &this->abi_area;
            *((uintptr_t*)address_for_func) = (uintptr_t)func_ptr;

            void* address_for_this = ((unsigned char*)&this->abi_area) + sizeof(void*);

            *((uintptr_t*)address_for_this) = (uintptr_t)this;
            
        }

        TF tf;

        int a;
};

void subscribe_proxy(int num, void* p){
    C1* pC1 = (C1*)p;
    pC1->sub_foo(num);
}


int main(){
    C1 c1(100);
    c1.subscribe_to_c_lib();

    C1 c2(200);
    c2.subscribe_to_c_lib();
    return 0;
}