/* Demetre Seturidze
 * Library
 * Basics
 */

#include"./basics.h"

const byte bytemask[byte_size] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void move(void* arr1, void* arr2, nat byteLen) {
    byte* target = (byte*)arr1;
    byte* source = (byte*)arr2;

    // moves arr2 into arr1 and frees arr2
    for (nat i = 0; i < byteLen; i++)
        target[i] = source[i];
    
    free(arr2);
}


/* PRINTS */

void println() {
    putchar('\n');
}


void print_boolean(boolean b) {
    if (b) putchar('1');
    else putchar('0');
}

void println_boolean(boolean b) {
    print_boolean(b); println();
}


void print_char(char c) {
    putchar(c);
}

void println_char(char c) {
    print_char(c);
    println();
}


void print_int(int i) {
    printf("%d", i);
}

void println_int(int i) {
    print_int(i);
    println();
}


void print_nat(nat i) {
    printf("%u", i);
}

void println_nat(nat i){
    print_nat(i); println();
}


void print_double(double i) {
    printf("%.8f", i);
}

void println_double(double i) {
    print_double(i);
    println();
}


void print_cstr(cstr c) {
    printf("%s", c);
}

void println_cstr(cstr c) {
    print_cstr(c); println();
}


void print_byte(byte b) {
    for (byte i = 0; i < byte_size; i++) 
        if (b & bytemask[i]) print_char('1');
        else print_char('0');
}

void println_byte(byte b) {
    print_byte(b); println();
}

// returns true if directory exists
boolean dir_exists(cstr dir) {
    // with the help of chatgpt
    struct stat info;
    return stat(dir, &info) == 0 && (S_ISDIR(info.st_mode)) ? True : False;
}
