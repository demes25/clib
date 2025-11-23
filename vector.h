/* Demetre Seturidze
 * Library
 * Vectors
 * [Header]
 */

#ifndef VECTOR
#define VECTOR

#include"./basics.h"
#include"./math.h"
#include"./text.h"

typedef struct Vector {
    double* vec;
    nat len;
    
    nat refs;
} Vector;

// back-end ("behind the scenes") functions

Vector* bts__emptyVector();
void bts__wipeVector(Vector* vec);
void bts__deleteVector(Vector* vec);
void bts__initVector(Vector* vec, nat len);

void bts__addVector(Vector* result, Vector* u, Vector* v);
void bts__subVector(Vector* result, Vector* u, Vector* v);
void bts__scaleVector(Vector* result, double a, Vector* u);
void bts__dotVector(double* result, Vector* u, Vector* v);

void bts__actOnComponents(Vector* result, double (*func)(double), Vector* u);
void bts__probabilityVector(Vector* u);
void bts__convolveVector(Vector* result, Vector* kernel, Vector* u);

boolean bts__read_Vector(Vector* empty, cstr filename);


// front-end functions
void print_Vector(Vector* u);
void print_T_Vector(Vector* u);
void println_Vector(Vector* u);
void println_T_Vector(Vector* u);

void deleteVector(Vector* u);
Vector* newVector(nat len);
Vector* copyVector(Vector* u);

double getComponent(Vector* u, nat i);
void setComponent(Vector* u, nat i, double r);

void fillRandom_Vector(Vector* u, double max);

boolean equalVector(Vector* u, Vector* v);
Vector* addVector(Vector* u, Vector* v);
Vector* subVector(Vector* u, Vector* v);
Vector* scaleVector(double a, Vector* u);
double dotVector(Vector* u, Vector* v);

Vector* actOnComponents(double (*func)(double), Vector* u);
Vector* probabilityVector(Vector* u);
Vector* convolveVector(Vector* k, Vector* u);

Vector* import_Vector(cstr filename);
boolean export_Vector(Vector* u, cstr filename);

#endif