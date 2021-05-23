#ifndef LIB_H

#define LIB_H

typedef void (*TF)(int);
typedef void (*TF2)(int, int);
void subscribe(void* f_ptr);

void subscribe2(void* f_ptr);

#endif