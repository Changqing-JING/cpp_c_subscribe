#include <cstring>
#include "APIFunction.h"
#include "MemoryUtils.hpp"

#ifdef x64
constexpr uint8_t bridge[] = {                    //push   rsi
    0x48, 0xb8, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11,  // movabs rax,0x1122334455667788
    
    0x4c, 0x8b, 0x78, 0x08,            // mov    r15,QWORD PTR [rax+0x8]
    0xff, 0x20,                  // call   QWORD PTR [rax]
    };

constexpr int abiOffset = 2;

void APIFunction::changeAddressInMachineCode(){
    char* address_holder = (char*)this->func + abiOffset;
    *((uintptr_t*)address_holder) = (uintptr_t)&abi_area;
}
#elif defined arm64
    constexpr uint32_t bridge[]={
        0xd28ef100,
        0xf2aaacc0,
        0xf2c66880,
        0xf2e22440,
        0xf940040f,
        0xf9400000,
        0xd61f0000
    };
    static constexpr uint32_t imm16Mask = 0b11111111'11111111'00000;
    static constexpr uint8_t imm16Offset = 5;

    void APIFunction::changeAddressInMachineCode(){
        uint32_t* machineCode = (uint32_t*)this->func;
        uintptr_t abi_address = (uintptr_t)&abi_area;
        
        while(abi_address>0){
            *machineCode &= ~(imm16Mask);
            *machineCode |= (abi_address & 0xFFFF)<<abi_address;

            machineCode += 1;
            abi_address >>= sizeof(uint16_t);
        }

    }
#endif

APIFunction::APIFunction(){
    this->func =  allocExecutableMemory(sizeof(bridge)); //fixme, use executeableHeap
    memcpy(this->func, bridge, sizeof(bridge));

    changeAddressInMachineCode();
}

APIFunction::~APIFunction(){
    if(this->func){
        freeAlignedMemroy((void*)this->func); 
    }
}

