/* Demetre Seturidze
 * Library
 * Matrices
 */

#include"./matrix.h"


Matrix* bts__emptyMatrix() {
    return (Matrix*)malloc(sizeof(Matrix));
}

void bts__wipeMatrix(Matrix* mtx) {
    for (nat i = 0; i < mtx -> width; i++)
        free(mtx -> cols[i]);
    free(mtx -> cols);
}

void bts__deleteMatrix(Matrix* mtx) {
    bts__wipeMatrix(mtx);
    free(mtx);
}

void bts__initMatrix(Matrix* mtx, nat h, nat w) {
    mtx -> height = h;
    mtx -> width = w;
    mtx -> cols = (double**)malloc(w * sizeof(double*));
    for (nat i = 0; i < w; i++)
        mtx -> cols[i] = (double*)malloc(h * sizeof(double));
    mtx -> refs = 0;
}



// 2d arrays are row-major, but we will be doing col-major.
// these DONT check for bounds
double getEntry(Matrix* mtx, nat i, nat j) {
    return mtx -> cols[j][i];
}

void setEntry(Matrix* mtx, nat i, nat j, double r) {
    mtx -> cols[j][i] = r;
}

Vector getColumn(Matrix* mtx, nat i) {
    return (Vector) {mtx -> cols[i], mtx -> height, 0};
}


void bts__addToEntry(Matrix* mtx, nat i, nat j, double r) {
    mtx -> cols[j][i] += r;
}


void bts__addMatrix(Matrix* result, Matrix* M, Matrix* N) {
    // returns M + N
    // M and N must have the SAME DIMENSIONS

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        setEntry(result, i, j,
            getEntry(M, i, j) + getEntry(N, i, j));
}

void bts__T_addMatrix(Matrix* result, Matrix* M, Matrix* N) {
    // returns M(transpose) + N
    // M and N must have M -> height == N -> width, M -> width == N -> height

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        setEntry(result, j, i,
            getEntry(M, i, j) + getEntry(N, i, j));
}


void bts__subMatrix(Matrix* result, Matrix* M, Matrix* N) {
    // returns M - N
    // M and N must have the SAME DIMENSIONS

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        setEntry(result, i, j,
            getEntry(M, i, j) - getEntry(N, i, j));
}

void bts__T_subMatrix(Matrix* result, Matrix* M, Matrix* N) {
    // returns M(transpose) - N
    // M and N must have M -> height == N -> width, M -> width == N -> height

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        setEntry(result, j, i,
            getEntry(M, i, j) - getEntry(N, i, j));
}

void bts__scaleMatrix(Matrix* result, double a, Matrix* M) {

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        result -> cols[j][i] = a * M -> cols[j][i];
}

void bts__mulMatrix(Matrix* result, Matrix* M, Matrix* N) {
    // returns M N
    // M width MUST EQUAL N height

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < N -> width; j++){
        setEntry(result, i, j, 0);
        for (nat k = 0; k < N -> height; k++)
            bts__addToEntry(result, i, j,
                getEntry(M, i, k) * getEntry(N, k, j));
    }
}

void bts__dotMatrix(Matrix* result, Matrix* M, Matrix* N) {
    // returns M(transpose) N
    // M height MUST EQUAL N height

    for (nat i = 0; i < M -> width; i++)
    for (nat j = 0; j < N -> width; j++){
        setEntry(result, i, j, 0);
        for (nat k = 0; k < N -> height; k++)
            bts__addToEntry(result, i, j,
                getEntry(M, k, i) * getEntry(N, k ,j));
    }
}

void bts__tenseMatrix(Matrix* result, Matrix* M, Matrix* N) {
    // returns M N(transpose)
    // M width MUST EQUAL N width

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < N -> height; j++){
        setEntry(result, i, j, 0);
        for (nat k = 0; k < N -> width; k++)
            bts__addToEntry(result, i, j,
                getEntry(M, i, k) * getEntry(N, j, k));
    }
}

void bts__transposeMatrix(Matrix* result, Matrix* M) {

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        result -> cols[i][j] = M -> cols[j][i];
}



void bts__actOnEntries(Matrix* result, double (*func)(double), Matrix* M) {

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        result -> cols[j][i] = func(M -> cols[j][i]);
}

void bts__probabilityMatrix(Matrix* M) {
    // returns M' : M'ij = Mij/sum(Mij)
    // such that the sum of all its entries is one.
    // result must have same dims as M
    double sum = 0;

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        sum += M -> cols[j][i];

    for (nat i = 0; i < M -> height; i++)
    for (nat j = 0; j < M -> width; j++)
        M -> cols[j][i] /= sum;
}

void bts__convolveMatrix(Matrix* result, Matrix* kernel, Matrix* M) {
    nat ilim = result -> height;
    nat jlim = result -> width;
    // result must have dimensions ilim x jlim

    for (nat i = 0; i < ilim; i++)
    for (nat j = 0; j < jlim; j++) {
        setEntry(result, i, j, 0);

        for (nat k = 0; k < kernel -> height; k++)
        for (nat l = 0; l < kernel -> width; l++)
            bts__addToEntry(result, i, j,
                getEntry(M, i + k, j + l) * 
                getEntry(kernel, k, l));
        
        // so ilim - 1 + k.height - 1 = M.height - 1

        // then:
        // ilim = M.height - k.height + 1
        // jlim = M.width - k.width + 1
    }
}


void bts__mulVector(Vector* result, Matrix* M, Vector* u) {
    // returns M u
    // M width must equal u len

    for (nat i = 0; i < M -> height; i++){
        result -> vec[i] = 0;

        for (nat j = 0; j < u -> len; j++)
            result -> vec[i] += (getEntry(M, i, j) * u -> vec[j]);
    } 
}

void bts__tenseVector(Matrix* result, Vector* u, Vector* v) {
    // returns u v(transpose)

    for (nat i = 0; i < u -> len; i++)
    for (nat j = 0; j < v -> len; j++){
        setEntry(result, i, j,
            u -> vec[i] * v -> vec[j]);
    }
}

void bts__probabilityColumns(Matrix* M) {
    // returns M' : M'ij = Mij/sum(Mkj)
    // such that the sum of the components of each column is one.
    // result must have same dims as M
    for (nat i = 0; i < M -> width; i++){
        Vector col = getColumn(M, i);
        bts__probabilityVector(&col);
    }
}



void print_Matrix(Matrix* mtx) {
    nat l = mtx -> height - 1;
    nat j = mtx -> width - 1;

    for (nat k = 0; k < l; k++) {
        print_char('[');
        for (nat i = 0; i < j; i++) {
            print_double(getEntry(mtx, k, i));
            print_cstr("  ");
        }
        print_double(getEntry(mtx, k, j));
        println_char(']');
    }

    print_char('[');
    for (nat i = 0; i < j; i++) {
        print_double(getEntry(mtx, l, i));
        print_cstr("  ");
    }
    print_double(getEntry(mtx, l, j));
    print_char(']');
}

void print_T_Matrix(Matrix* mtx) {
    nat l = mtx -> height - 1;
    nat j = mtx -> width - 1;

    for (nat k = 0; k < j; k++) {
        print_char('[');
        for (nat i = 0; i < l; i++) {
            print_double(getEntry(mtx, i, k));
            print_cstr("  ");
        }
        print_double(getEntry(mtx, l, k));
        println_char(']');
    }

    print_char('[');
    for (nat i = 0; i < l; i++) {
        print_double(getEntry(mtx, i, j));
        print_cstr("  ");
    }
    print_double(getEntry(mtx, l, j));
    print_char(']');
}


void println_Matrix(Matrix* mtx) {
    print_Matrix(mtx); println();
}

void println_T_Matrix(Matrix* mtx) {
    print_T_Matrix(mtx); println();
}



void deleteMatrix(Matrix* mtx) {
    if(mtx && !(mtx -> refs && --(mtx -> refs))) bts__deleteMatrix(mtx);
}

Matrix* newMatrix(nat h, nat w) {
    Matrix* result = bts__emptyMatrix();
    bts__initMatrix(result, h, w);
    return result;
}

Matrix* newCovector(nat w) {
    Matrix* result = bts__emptyMatrix();
    bts__initMatrix(result, 1, w);
    return result;
}

Matrix* identity(nat L) {
    Matrix* result = newMatrix(L, L);
    for (nat i = 0; i < L; i++)
    for (nat j = 0; j < L; j++)
        setEntry(result, i, j, i == j);
    return result;
}

Matrix* copyMatrix(Matrix* mtx) {
    Matrix* result = newMatrix(mtx -> height, mtx -> width);
    for (nat i = 0; i < mtx -> height; i++)
    for (nat j = 0; j < mtx -> width; j++)
        result -> cols[j][i] = mtx -> cols[j][i];

    return result;
}


void fillRandom(Matrix* mtx, double max) {
    if (mtx){
        for (nat i = 0; i < mtx -> height; i++)
        for (nat j = 0; j < mtx -> width; j++) 
            mtx -> cols[j][i] = randInRange(-max, max);
    }
}

boolean equalMatrix(Matrix* M, Matrix* N) {
    // returns M = N

    if (M == N) return True;

    else if ((M -> height != N -> height) || (M -> width != N -> width)) return False;

    else for (nat i = 0; i < M -> height; i++)
        for (nat j = 0; j < M -> width; j++)
            if (M -> cols[j][i] != N -> cols[j][i]) return False;
    
    return True;
}

boolean transequalMatrix(Matrix* M, Matrix* N) {
    // returns M(transpose) = N

    if (M -> height != N -> width || M -> width != N -> height) return False;

    else for (nat i = 0; i < M -> height; i++)
        for (nat j = 0; j < M -> width; j++)
            if (M -> cols[j][i] != N -> cols[i][j]) return False;

    return True;
}


Matrix* addMatrix(Matrix* M, Matrix* N) {
    if (M -> height != N -> height || M -> width != N -> width) return null;

    Matrix* result = newMatrix(M -> height, M -> width);
    bts__addMatrix(result, M, N);
    return result;
}

Matrix* addT_Matrix(Matrix* M, Matrix* N) {
    if (M -> width != N -> height || M -> height != N -> width) return null;

    Matrix* result = newMatrix(N -> height, N -> width);
    bts__T_addMatrix(result, M, N);
    return result;
}

Matrix* subMatrix(Matrix* M, Matrix* N) {
    if (M -> height != N -> height || M -> width != N -> width) return null;

    Matrix* result = newMatrix(M -> height, M -> width);
    bts__subMatrix(result, M, N);
    return result;
}

Matrix* subT_Matrix(Matrix* M, Matrix* N) {
    if (M -> width != N -> height || M -> height != N -> width) return null;

    Matrix* result = newMatrix(N -> height, N -> width);
    bts__T_subMatrix(result, M, N);
    return result;
}

Matrix* scaleMatrix(double a, Matrix* M) {
    Matrix* result = newMatrix(M -> height, M -> width);
    bts__scaleMatrix(result, a, M);
    return result;
}

Matrix* mulMatrix(Matrix* M, Matrix* N) {
    if (M -> width != N -> height) return null;

    
    Matrix* result = newMatrix(M -> height, N -> width);
    bts__mulMatrix(result, M, N);
    return result;
}

Matrix* dotMatrix(Matrix* M, Matrix* N) {
    if (M -> height != N -> height) return null;

    Matrix* result = newMatrix(M -> width, N -> width);
    bts__dotMatrix(result, M, N);
    return result;
}

Matrix* tenseMatrix(Matrix* M, Matrix* N) {
    if (M -> width != N -> width) return null;

    Matrix* result = newMatrix(M -> height, N -> height);
    bts__tenseMatrix(result, M, N);
    return result;
}

Matrix* transposeMatrix(Matrix* M) {

    Matrix* result = newMatrix(M -> width, M -> height);
    bts__transposeMatrix(result, M);
    return result;
}


Matrix* actOnEntries(double (*func)(double), Matrix* M) {
    Matrix* result = newMatrix(M -> height, M -> width);
    bts__actOnEntries(result, *func, M);
    return result;
}

Matrix* probabilityMatrix(Matrix* M) {
    // normalizes M' : M'ij -> Mij/sum(Mkl)
    // such that the sum of the components of each column is one.

    Matrix* result = copyMatrix(M);
    bts__probabilityMatrix(result);
    return result;
}

Matrix* convolveMatrix(Matrix* k, Matrix* M) {
    Matrix* result = null;

    if (k -> height < M -> height && k -> width < M -> width) {
        result = newMatrix(M -> height - k -> height + 1, M -> width - k -> width + 1);
        bts__convolveMatrix(result, k, M);
    } else if (k -> height > M -> height && k -> width > M -> width) {
        result = newMatrix(k -> height - M -> height + 1, k -> width - M -> width + 1);
        bts__convolveMatrix(result, M, k);
    } else {
        // do something!! throw an error or something.
    } 

    return result;
}



Vector* copyColumn(Matrix* M, nat i) {
    // i must be within bounds.
    Vector* result = newVector(M -> height);
    for (nat j = 0; j < M -> height; j++)
        result -> vec[j] = getEntry(M, j, i);
    return result;
}

Vector* mulVector(Matrix* M, Vector* u) {
    // returns M u
    // M width must equal u len

    if (M -> width != u -> len) return null;

    Vector* result = newVector(M -> height);
    bts__mulVector(result, M, u);
    return result;
}

Matrix* tenseVector(Vector* u, Vector* v) {
    // returns u v(transpose)
    Matrix* result = newMatrix(u -> len, v -> len);
    bts__tenseVector(result, u, v);
    return result;
}

Matrix* probabilityColumns(Matrix* M) {
    // normalizes M' : M'ij -> Mij/sum(Mkj)
    // such that the sum of the components of each column is one.
    
    Matrix* result = copyMatrix(M);
    bts__probabilityColumns(M);
    return result;
}





boolean bts__read_Matrix(Matrix* empty, cstr filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) return False;

    // formatting (NO COMMENTS):
    // 
    // M,h,w
    // (mtx)

    char M; nat h, w;

    if (fscanf(file, "%c,%d,%d\n", &M, &h, &w) < 0 ||
        (M != 'M' || h < 0 || w < 0)) return False;

    bts__initMatrix(empty, h, w);
    double temp;

    nat lastCol = w -1;

    for (nat i = 0; i < h; i++){
        if (fscanf(file, "%lf", &temp) < 0)
            return False;
        setEntry(empty, i, 0, temp);

        for (nat j = 1; j < lastCol; j++){
            if (fscanf(file, ",%lf", &temp) < 0)
                return False;
            setEntry(empty, i, j, temp);
        }

        if (fscanf(file, ",%lf\n", &temp) < 0)
            return False;
        setEntry(empty, i, lastCol, temp);
    }

    fclose(file);

    return True;

}

Matrix* import_Matrix(cstr filename) {
    Matrix* m = bts__emptyMatrix();
    if (bts__read_Matrix(m, filename)) return m;
    else {deleteMatrix(m); return null;}
}

boolean export_Matrix(Matrix* m, cstr filename) {
    // b MUST NOT BE EMPTY

    FILE* file = fopen(filename, "w");

    if (file == NULL) return False;

    // formatting:
    // 
    // M,h,w
    // (mtx)

    if (fprintf(file, "M,%d,%d\n", m -> height, m -> width) < 0) return False;

    nat lastCol = m -> width - 1;

    for (nat i = 0; i < m -> height; i++){
        for (nat j = 0; j < lastCol; j++)
            if (fprintf(file, "%.15lf,", getEntry(m, i, j)) < 0)
                return False;

        if (fprintf(file, ",%.15lf\n", getEntry(m, i, lastCol)) < 0)
            return False;
    }

    fclose(file);

    return True;
}



