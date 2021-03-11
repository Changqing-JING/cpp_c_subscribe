#include <cstdio>
#include <cstdint>
#include <cstring>
#include "MemoryUtils.hpp"

extern "C"{
    #include "lib.h"
}

#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#else
#error "Unsupported OS"

#endif

void subscribe_proxy(int num, void* p);

unsigned char bridge[] = {   0x53 ,                     //push   rbx
         0x56,                      //push   rsi
     0x48, 0xb8, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11,  // movabs rax,0x1122334455667788
      
      0x48, 0x8b, 0x18,                //mov    rbx,QWORD PTR [rax]
       0x48, 0x8b, 0x70, 0x08,            // mov    rsi,QWORD PTR [rax+0x8]
     0xff, 0xd3,                  // call   rbx
     0x5e,                     // pop    rsi
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
        void* abi_area[2];

        void gerertion_function(){
            this->tf = (TF)allocExecutableMemory(4096);
            memcpy((void*)this->tf, bridge, sizeof(bridge));
            char* address_holder = (char*)this->tf + 4;
            *((uintptr_t*)address_holder) = (uintptr_t)this->abi_area;

            abi_area[0] = (void*)&subscribe_proxy;
            abi_area[1] = this;          
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