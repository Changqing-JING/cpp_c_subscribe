#include "lib.h"

void subscribe(void* f_ptr){
    ((TF)f_ptr)(5);
}

void subscribe2(void* f_ptr){
    ((TF2)f_ptr)(1, 2);
}