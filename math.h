/* Demetre Seturidze
 * Library
 * Math
 * [Header]
 */

#ifndef MATH
#define MATH

#include"./basics.h"
#include<math.h>
#include<complex.h>

#define E  2.71828182846
#define PI 3.14159265359
#define TAU 6.28318530718

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALT(a) ((a % 2 == 0) ? 1 : -1)

typedef double complex Complex;

nat delta(int i, int k);
int theta(double i);
int step(double i);

double square(double r);
double randInRange(double a, double b);


#endif