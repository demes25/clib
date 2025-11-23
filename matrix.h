/* Demetre Seturidze
 * Library
 * Matrices
 * [Header]
 */

#ifndef MATRIX
#define MATRIX

#include"./basics.h"
#include"./vector.h"


typedef struct Matrix {
    double** cols;

    nat height;
    nat width;
    
    nat refs;
} Matrix;

Matrix* bts__emptyMatrix();

void bts__wipeMatrix(Matrix* mtx);
void bts__deleteMatrix(Matrix* mtx);

void bts__initMatrix(Matrix* mtx, nat h, nat w);


double getEntry(Matrix* mtx, nat i, nat j);
void setEntry(Matrix* mtx, nat i, nat j, double r);

Vector getColumn(Matrix* mtx, nat i);

void bts__addToEntry(Matrix* mtx, nat i, nat j, double r);

void bts__addMatrix(Matrix* result, Matrix* M, Matrix* N);

void bts__T_addMatrix(Matrix* result, Matrix* M, Matrix* N);
void bts__subMatrix(Matrix* result, Matrix* M, Matrix* N);

void bts__T_subMatrix(Matrix* result, Matrix* M, Matrix* N);
void bts__scaleMatrix(Matrix* result, double a, Matrix* M);

void bts__mulMatrix(Matrix* result, Matrix* M, Matrix* N);
void bts__dotMatrix(Matrix* result, Matrix* M, Matrix* N);

void bts__tenseMatrix(Matrix* result, Matrix* M, Matrix* N);
void bts__transposeMatrix(Matrix* result, Matrix* M);



void bts__actOnEntries(Matrix* result, double (*func)(double), Matrix* M);

void bts__probabilityMatrix(Matrix* M);
void bts__mulVector(Vector* result, Matrix* M, Vector* u);

void bts__tenseVector(Matrix* result, Vector* u, Vector* v);
void bts__probabilityColumns(Matrix* M);



void print_Matrix(Matrix* mtx);
void print_T_Matrix(Matrix* mtx);

void println_Matrix(Matrix* mtx);
void println_T_Matrix(Matrix* mtx);


void deleteMatrix(Matrix* mtx);

Matrix* newMatrix(nat h, nat w);
Matrix* newCovector(nat w);

Matrix* identity(nat L);

Matrix* copyMatrix(Matrix* mtx);

void fillRandom(Matrix* mtx, double max);
boolean equalMatrix(Matrix* M, Matrix* N);

boolean transequalMatrix(Matrix* M, Matrix* N);
Matrix* addMatrix(Matrix* M, Matrix* N);

Matrix* addT_Matrix(Matrix* M, Matrix* N);
Matrix* subMatrix(Matrix* M, Matrix* N);
Matrix* subT_Matrix(Matrix* M, Matrix* N);
Matrix* scaleMatrix(double a, Matrix* M);

Matrix* mulMatrix(Matrix* M, Matrix* N);

Matrix* dotMatrix(Matrix* M, Matrix* N);

Matrix* tenseMatrix(Matrix* M, Matrix* N);
Matrix* transposeMatrix(Matrix* M);


Matrix* actOnEntries(double (*func)(double), Matrix* M);

Matrix* probabilityMatrix(Matrix* M);

Matrix* convolveMatrix(Matrix* k, Matrix* M);


Vector* copyColumn(Matrix* M, nat i);

Vector* mulVector(Matrix* M, Vector* u);
Matrix* tenseVector(Vector* u, Vector* v);
Matrix* probabilityColumns(Matrix* M);




boolean bts__read_Matrix(Matrix* empty, cstr filename);

Matrix* import_Matrix(cstr filename);
boolean export_Matrix(Matrix* m, cstr filename);

#endif