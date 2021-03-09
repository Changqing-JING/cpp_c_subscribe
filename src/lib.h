#ifndef LIB_H

#define LIB_H

typedef void (*TF)(int);

void subscribe(TF f_ptr);

#endif