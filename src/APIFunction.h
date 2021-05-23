#pragma once
#include <cstdint>
#include <array>
#include "CPUAdapter.h"




struct APIFunction{
        void* func;
        std::array<void*, 2> abi_area;
        APIFunction();
        ~APIFunction();

        private:
            void changeAddressInMachineCode();
};