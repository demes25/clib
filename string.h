/* Demetre Seturidze
 * Library
 * Strings
 * [Header]
 */

#ifndef STRING
#define STRING

#define init_string_size 50
#define init_hash 2166136261
#define hash_prime 16777619

#define new_line '\n'
#define tab '\t'
#define space ' '
#define is_punct(a) (((a) > 33 && (a) <= 47) || ((a) > 91 && (a) <= 96) || ((a) > 123 && (a) <= 126))


#include"./basics.h"


typedef struct String {
    char* str;
    nat len;
    nat size;

    nat hash;
    
    nat refs;
} String;

// back-end ("behind the scenes") functions

String* bts__emptyString();
void bts__wipeString(String* str);
void bts__deleteString(String* str);
void bts__initString(String* str);

void bts__resizeString(String* str);
void bts__updateHash(String* str, char c);
void bts__stringAppend(String* str, char c);


// front-end functions

char getChar(String* str, nat i);
char getFirstChar(String* str);
char getLastChar(String* str);

/*
boolean setChar(String* str, nat i, char c);
boolean setFirstChar(String* str, char c);
boolean setLastChar(String* str, char c);
*/ 

boolean stringAppend(String* str, char c);
void stringAppend_cstr(String* str, cstr c);
void stringAppend_String(String* str, String* s);


boolean equalStrings(String* s1, String* s2);
boolean equalStrings_cstr(String* s1, cstr s2);


void print_String(String* str);
void println_String(String* str);

void deleteString(String* str);
String* newString();
String* newString_char(char c);
String* newString_cstr(cstr c);
String* copyString(String* str);





#endif