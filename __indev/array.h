/* Demetre Seturidze
 * Library
 * Arrays
 * [Header]
 */

#ifndef ARRAY
#define ARRAY

#define init_arr_size 10

#include"../basics.h"


typedef struct Array {
    double* arr;
    nat len;
    nat size;
    
    nat refs;
} Array;

// back-end ("behind the scenes") functions

Array* bts__emptyArray();
void bts__wipeArray(Array* arr);
void bts__deleteArray(Array* arr);
void bts__initArray(Array* arr);

void bts__resizeArray(Array* arr);


// front-end functions

double getItem(Array* arr, nat i);
double setItem(Array* arr, nat i, double n);

boolean arrayAppend(Array* arr, double n);
void arrayAppend_dptr(Array* arr, double* N, nat size);
void arrayAppend_Array(Array* arr, Array* a);


boolean equalArrays(Array* s1, Array* s2);


void print_Array(Array* arr);
void println_Array(Array* arr);

void deleteArray(Array* arr);
Array* newArray();
Array* newArray_size(nat size);
Array* newArray_double(double n);
Array* newArray_dptr(double* N, nat size);
Array* copyArray(Array* arr);





#endif