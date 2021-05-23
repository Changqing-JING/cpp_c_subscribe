#pragma once
#include <vector>
#include <array>
#include <memory>
#include "APIFunction.h"

extern "C"{
    #include "lib.h"

}



class C1{
    
    public:
        C1(int a);

       ~C1();

        void sub_foo(int input);
        int sub_foo2(int input1, int input2);

        void subscribe_to_c_lib();

        
    private:
        void* gerertion_function(void* bridgeFunction);
        std::vector<std::unique_ptr<APIFunction>> apiFunctions;

        int a;
};
