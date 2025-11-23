/* Demetre Seturidze
 * Library
 * Strings
 */


#include"./string.h"


String* bts__emptyString() {
    return (String*)malloc(sizeof(String));
}

void bts__wipeString(String* str) {
    free(str -> str);
}

void bts__deleteString(String* str) {
    bts__wipeString(str);
    free(str);
}

void bts__initString(String* str) {
    str -> len = 0;
    str -> size = init_string_size;
    str -> str = (char*)malloc(init_string_size * sizeof(char));
    str -> hash = init_hash;
    str -> refs = 0;
}

void bts__resizeString(String* str) {
    str -> size *= resize_ratio;
    char* newCharPtr = (char*)malloc(str -> size * sizeof(char));

    move(newCharPtr, str -> str, str -> len * sizeof(char));

    str -> str = newCharPtr;
}

void bts__updateHash(String* str, char c) {
    str -> hash ^= c;
    str -> hash *= hash_prime;
    str -> hash &= nat_max;
}

void bts__stringAppend(String* str, char c) {
    if (str -> len + 1 >= str -> size) {bts__resizeString(str);}
    str -> str[str -> len++] = c;
    str -> str[str -> len] = null;
    bts__updateHash(str, c);
}


char getChar(String* str, nat i) {
    // returns the null terminator if out of bounds
    if (i > str -> len) return null;
    else return str -> str[i];
}

char getFirstChar(String* str) {
    return getChar(str, 0);
}

char getLastChar(String* str) {
    return getChar(str, str -> len - 1);
}

/* these fuck with the hash, fix this.
boolean setChar(String* str, nat i, char c) {
    // returns false if out of bounds
    if (!c || i > str -> len) return False;
    else {str -> str[i] = c; return True;}
}

boolean setFirstChar(String* str, char c) {
    return setChar(str, 0, c);
}

boolean setLastChar(String* str, char c) {
    return setChar(str, str -> len - 1, c);
}
*/ 

boolean stringAppend(String* str, char c) {
    if (!c) return False;
    else {
        bts__stringAppend(str, c);
        return True;
    }
}

void stringAppend_cstr(String* str, cstr c) {
    for (nat i = 0; c[i]; i++) {bts__stringAppend(str, c[i]);}
}

void stringAppend_String(String* str, String* s) {
    for (nat i = 0; i < s -> len; i++) {bts__stringAppend(str, s -> str[i]);}
}


boolean equalStrings(String* s1, String* s2) {
    if (s1 == s2) return True;

    else if (s1 -> len != s2 -> len || s1 -> hash != s2 -> hash) return False;

    else for (nat i = 0; i < s1 -> len; i++)
        if (s1 -> str[i] != s2 -> str[i]) return False;
    
    return True;
}

boolean equalStrings_cstr(String* s1, cstr s2) {
    nat i = 0;
    for (; s2[i]; i++)
        if (s1 -> str[i] != s2[i]) return False;
    
    return i == s1 -> len ? True : False;
}


void print_String(String* str) {
    for (nat i = 0; i < str -> len; i++) print_char(str -> str[i]);
}

void println_String(String* str) {
    print_String(str); println();
}


void deleteString(String* str) {
    if (str && !(str -> refs && --(str -> refs))) bts__deleteString(str);
}

String* newString() {
    String* result = bts__emptyString();
    bts__initString(result);
    return result;
}

String* newString_char(char c) {
    if (!c) return newString();

    String* result = bts__emptyString();
    bts__initString(result);
    bts__stringAppend(result, c);
    return result;
}

String* newString_cstr(cstr c) {
    String* result = bts__emptyString();
    bts__initString(result);
    stringAppend_cstr(result, c);
    return result;
}

String* copyString(String* str) {
    String* result = bts__emptyString();
    bts__initString(result);
    stringAppend_String(result, str);
    return result;
}
