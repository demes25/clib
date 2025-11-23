/* Demetre Seturidze
 * Library
 * Array
 */


#include"./array.h"


Array* bts__emptyArray() {
    return (Array*)malloc(sizeof(Array));
}

void bts__wipeArray(Array* arr) {
    free(arr -> arr);
}

void bts__deleteArray(Array* arr) {
    bts__wipeArray(arr);
    free(arr);
}

void bts__initArray(Array* arr, nat size) {
    arr -> len = 0;
    arr -> size = size;
    arr -> arr = (double*)malloc(size * sizeof(double));
    arr -> refs = 0;
}

void bts__resizeArray(Array* arr) {
    arr -> size *= resize_ratio;
    double* newPtr = (double*)malloc(arr -> size * sizeof(double));

    move(newPtr, arr -> arr, arr -> len * sizeof(double));

    arr -> arr = newPtr;
}



double getItem(Array* arr, nat i) {
    return arr -> arr[i];
}

double setItem(Array* arr, nat i, double n) {
    arr -> arr[i] = n;
}



void arrayAppend(Array* arr, double n) {
    if (arr -> len + 1 >= arr -> size) {bts__resizeArray(arr);}
    arr -> arr[arr -> len++] = n;
}

void arrayAppend_dptr(Array* arr, double* N, nat size) {
    for (nat i = 0; i < size; i++) {bts__ArrayAppend(arr, N[i]);}
}

void arrayAppend_Array(Array* arr, Array* a) {
    for (nat i = 0; i < a -> len; i++) {bts__ArrayAppend(arr, a -> arr[i]);}
}


boolean equalArrays(Array* a1, Array* a2) {
    if (a1 == a2) return True;

    else if (a1 -> len != a2 -> len) return False;

    else for (nat i = 0; i < a1 -> len; i++)
        if (a1 -> arr[i] != a2 -> arr[i]) return False;
    
    return True;
}


void print_Array(Array* arr) {
    print_char('[');
    nat fin = arr -> len - 1;
    for (nat i = 0; i < fin; i++) {
        print_double(arr -> arr[i]);
        print_char(','); print_char(' ');
    }
    print_double(arr -> arr[fin]); print_char(']');
}

void println_Array(Array* arr) {
    print_Array(arr); println();
}


void deleteArray(Array* arr) {
    if (arr && !(arr -> refs && --(arr -> refs))) bts__deleteArray(arr);
}

Array* newArray() {
    Array* result = bts__emptyArray();
    bts__initArray(result, init_arr_size);
    return result;
}

Array* newArray_size(nat size) {
    Array* result = bts__emptyArray();
    bts__initArray(result, size);
    return result;
}

Array* newArray_double(double n) {
    Array* result = newArray();
    bts__ArrayAppend(result, n);
    return result;
}

Array* newArray_dptr(double* N, nat size) {
    Array* result = bts__emptyArray();
    bts__initArray(result, size + 1);
    ArrayAppend_dptr(result, N, size);
    return result;
}

Array* copyArray(Array* arr) {
    Array* result = bts__emptyArray();
    bts__initArray(result, arr -> len + 1);
    ArrayAppend_Array(result, arr);
    return result;
}
