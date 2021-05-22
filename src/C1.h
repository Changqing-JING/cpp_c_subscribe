#pragma once
extern "C"{
    #include "lib.h"
}


class C1{
    public:
        C1(int a);

       ~C1();

        void sub_foo(int input);

        void subscribe_to_c_lib();

        
    private:
        void* abi_area[2];

        void gerertion_function();

        TF tf;

        int a;
};
