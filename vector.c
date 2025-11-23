/* Demetre Seturidze
 * Library
 * Vectors
 */

#include"./vector.h"


Vector* bts__emptyVector() {
    return (Vector*)malloc(sizeof(Vector));
}

void bts__wipeVector(Vector* vec) {
    free(vec -> vec);
}

void bts__deleteVector(Vector* vec) {
    bts__wipeVector(vec);
    free(vec);
}

void bts__initVector(Vector* vec, nat len) {
    vec -> len = len;
    vec -> vec = (double*)malloc(len * sizeof(double));
    vec -> refs = 0;
}


void bts__addVector(Vector* result, Vector* u, Vector* v) {
    // returns u + v
    // u and v must have same length

    for (nat j = 0; j < u -> len; j++)
        result -> vec[j] = u -> vec[j] + v -> vec[j];
}

void bts__subVector(Vector* result, Vector* u, Vector* v) {
    // returns u - v
    // u and v must have the SAME LENGTH

    for (nat j = 0; j < u -> len; j++)
        result -> vec[j] = u -> vec[j] - v -> vec[j];
}

void bts__scaleVector(Vector* result, double a, Vector* u) {
    for (nat j = 0; j < u -> len; j++)
        result -> vec[j] = a * u -> vec[j];
}

void bts__dotVector(double* result, Vector* u, Vector* v) {
    // returns u(transpose) v
    // u and v must have same length
    double temp = 0;
    
    for (nat j = 0; j < u -> len; j++)
        temp += (u -> vec[j] * v -> vec[j]);
    
    *result = temp;
}


void bts__actOnComponents(Vector* result, double (*func)(double), Vector* u) {
    for (nat j = 0; j < u -> len; j++)
        result -> vec[j] = func(u -> vec[j]);
}

void bts__probabilityVector(Vector* u) {
    // normalizes : u[i] -> u[i]/sum(u[j])
    // such that the sum of all its entries is one.
    double sum = 0;

    for (nat j = 0; j < u -> len; j++)
        sum += u -> vec[j];

    for (nat j = 0; j < u -> len; j++)
        u -> vec[j] /= sum;
}

void bts__convolveVector(Vector* result, Vector* kernel, Vector* u) {
    nat ilim = result -> len;
    // result must have dimensions ilim x jlim

    for (nat i = 0; i < ilim; i++){
        result -> vec[i] = 0;

        for (nat l = 0; l < kernel -> len; l++)
            result -> vec[i] += (
                (u -> vec[i + l]) * 
                (kernel -> vec[l])
            );
        
        // so ilim - 1 + k.len - 1 = u.len - 1
        // then ilim = u.len - k.len + 1
    }
}


void print_Vector(Vector* u) {
    nat l = u -> len - 1;

    for (nat k = 0; k < l; k++) {
        print_char('[');
        print_double(u -> vec[k]);
        println_char(']');
    }

    print_char('[');
    print_double(u -> vec[l]);
    print_char(']');
}

void print_T_Vector(Vector* u) {
    nat l = u -> len - 1;

    print_char('[');

    for (nat k = 0; k < l; k++) {
        print_double(u -> vec[k]);
        print_cstr("  ");
    }

    print_double(u -> vec[l]);
    print_char(']');
}


void println_Vector(Vector* u) {
    print_Vector(u); println();
}

void println_T_Vector(Vector* u) {
    print_T_Vector(u); println();
}



void deleteVector(Vector* u) {
    if(u && !(u -> refs && --(u -> refs))) bts__deleteVector(u);
}

Vector* newVector(nat len) {
    Vector* result = bts__emptyVector();
    bts__initVector(result, len);
    return result;
}

Vector* copyVector(Vector* u) {
    Vector* result = newVector(u -> len);
    for (nat j = 0; j < u -> len; j++)
        result -> vec[j] = u -> vec[j];

    return result;
}


double getComponent(Vector* u, nat i) {
    return u -> vec[i];
}

void setComponent(Vector* u, nat i, double r) {
    u -> vec[i] = r;
}


void fillRandom_Vector(Vector* u, double max) {
    if (u){
        for (nat i = 0; i < u -> len; i++)
            u -> vec[i] = randInRange(-max, max);
    }
}

boolean equalVector(Vector* u, Vector* v) {
    // returns M = N

    if (u == v) return True;

    else if (u -> len != v -> len) return False;

    else for (nat i = 0; i < u -> len; i++)
        if (u -> vec[i] != v -> vec[i]) return False;
    
    return True;
}

Vector* addVector(Vector* u, Vector* v) {
    if (u -> len != v -> len) return null;

    Vector* result = newVector(u -> len);
    bts__addVector(result, u, v);
    return result;
}

Vector* subVector(Vector* u, Vector* v) {
    if (u -> len != v -> len) return null;

    Vector* result = newVector(u -> len);
    bts__subVector(result, u, v);
    return result;
}

Vector* scaleVector(double a, Vector* u) {
    Vector* result = newVector(u -> len);
    bts__scaleVector(result, a, u);
    return result;
}

double dotVector(Vector* u, Vector* v) {
    // if (u -> len != v -> len) throw an error;

    double result;
    bts__dotVector(&result, u, v);
    return result;
}


Vector* actOnComponents(double (*func)(double), Vector* u) {
    Vector* result = newVector(u -> len);
    bts__actOnComponents(result, func, u);
    return result;
}

Vector* probabilityVector(Vector* u) {
    Vector* result = copyVector(u);
    bts__probabilityVector(result);
    return result;
}


Vector* convolveVector(Vector* k, Vector* u) {
    Vector* result = null;

    if (k -> len < u -> len) {
        result = newVector(u -> len - k -> len + 1);
        bts__convolveVector(result, k, u);
    } else {
        result = newVector(k -> len - u -> len + 1);
        bts__convolveVector(result, u, k);
    }

    return result;
}


boolean bts__read_Vector(Vector* empty, cstr filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) return False;

    // formatting (NO COMMENTS):
    // 
    // V,len
    // (vec)

    char V; nat len;

    nat count;

    if (fscanf(file, "%c,%d\n", &V, &len) < 0 ||
        (V != 'V' || len <= 0)) return False;

    bts__initVector(empty, len);
    double temp;

    nat lastEntry = len-1;

    for (nat j = 0; j < lastEntry; j++){
        if (fscanf(file, "%lf,", &temp) < 0)
            return False;
        empty -> vec[j] = temp;
    }

    if (fscanf(file, "%lf\n", &temp) < 0)
        return False;
    empty -> vec[lastEntry] = temp;


    fclose(file);

    return True;

}

Vector* import_Vector(cstr filename) {
    Vector* m = bts__emptyVector();
    if (bts__read_Vector(m, filename)) return m;
    else {deleteVector(m); return null;}
}

boolean export_Vector(Vector* u, cstr filename) {
    // u MUST NOT BE EMPTY

    FILE* file = fopen(filename, "w");

    if (file == NULL) return False;

    // formatting:
    // 
    // V,len
    // (vec)

    if (fprintf(file, "V,%d\n", u -> len) < 0) return False;

    nat lastEntry = u -> len - 1;

    for (nat j = 0; j < lastEntry; j++)
        if (fprintf(file, "%.15lf,", u -> vec[j]) < 0)
            return False;

    if (fprintf(file, "%.15lf\n", u -> vec[lastEntry]) < 0)
        return False;

    fclose(file);

    return True;
}
