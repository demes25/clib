/* Demetre Seturidze
 * Library
 * Basics
 * [Header]
 */

#ifndef BASICS
#define BASICS

#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>


#define null 0
#define byte_size 8
#define resize_ratio 2

#define nat_max 0xffffffff
#define byte_max 0xff

typedef size_t capacity;
typedef unsigned int nat;
typedef unsigned char byte;
typedef const char* cstr;

extern const byte bytemask[byte_size];

typedef enum {
    False = 0,
    True = 1
} boolean;

void move(void* arr1, void* arr2, nat byteLen);

void println();

void print_boolean(boolean b);
void println_boolean(boolean b);

void print_char(char c);
void println_char(char c);

void print_int(int i);
void println_int(int i);

void print_nat(nat i);
void println_nat(nat i);

void print_double(double i);
void println_double(double i);

void print_cstr(cstr c);
void println_cstr(cstr c);

void print_byte(byte b);
void println_byte(byte b);

boolean dir_exists(cstr dir);

#endif