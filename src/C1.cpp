#include <cstdio>
#include <cstdint>
#include <cstring>


#include "C1.h"
#include "MemoryUtils.hpp"
#include "CCPPProxy.h"

C1::APIFunction::APIFunction(){
    this->func =  allocExecutableMemory(sizeof(bridge)); //fixme, use executeableHeap
    memcpy(this->func, bridge, sizeof(bridge));

    char* address_holder = (char*)this->func + abiOffset;
    *((uintptr_t*)address_holder) = (uintptr_t)&abi_area;
}

C1::APIFunction::~APIFunction(){
    if(this->func){
        freeAlignedMemroy((void*)this->func); 
    }
}

C1::C1(int a)
{
    this->a = a;
    
}

C1::~C1(){ 
    
   
}


void C1::sub_foo(int input){
    int result = this->a + input;
    printf("result is %d\n", result);
}

int C1::sub_foo2(int input1, int input2){
    
    printf("result is %d, %d, %d\n", this->a, input1, input2);
    return input1 + input2;
}

void C1::subscribe_to_c_lib(){

    void* tf = gerertion_function( (void*)&(ClassMemberFuctionBind<C1, void, int>::call<&C1::sub_foo>));
    void* tf2 = gerertion_function((void*)&(ClassMemberFuctionBind<C1, int, int , int>::call<&C1::sub_foo2>));
    
    subscribe(tf);
    subscribe2(tf2);
}

void* C1::gerertion_function( void* bridgeFunction){
     
    apiFunctions.push_back(std::unique_ptr<APIFunction>(new APIFunction()));
    std::unique_ptr<APIFunction>& apiFunction = apiFunctions.back();

    apiFunction->abi_area = {bridgeFunction, (void*)this};
    
    return apiFunction->func;        
       
}