/* Demetre Seturidze
 * Library
 * Math
 */

#include"./math.h"

nat delta(int i, int k) {
    return i == k;
}

int theta(double i) {
    return i < 0 ? -1 : 1;
}

int step(double i) {
    return (i >= 0);
}


double square(double r) {
    return r * r;
}

double randInRange(double a, double b) {
    return (a + ((double)rand()/RAND_MAX)*(b - a));
}


/*
const int _expLim = 10;

//const double _Logs[10] = {}

const int _factorial[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800}; 

const int _primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
const double _primeSqrts[10] = {1.41421356237, 1.73205080757, 2.2360679775, 2.64575131106, 3.31662479036, 3.60555127546, 4.12310562562, 4.35889894354, 4.79583152331, 5.38516480713};

const double _specialAngles[8] = {0, PI/6, PI/4, PI/3, PI/2, 2 * PI/3, 3 * PI/4, PI};
const double _specialSin[8] = {0, 0.5, 1/1.41421356237, 1.73205080757/2, 1, 1.73205080757/2, 1/1.41421356237, 0.5};
const double _specialCos[8] = {1, 1.73205080757/2,  1/1.41421356237, 0.5, 0, -0.5, -1/1.41421356237, -1.73205080757/2};





int alt(int i) {
    return i % 2 == 0 ? 1 : -1;
}

double intPow(double r, int n) {
    if (n < 0) return 1/intPow(r, -n);
    else if (n == 0) return 1.0;
    else if (n == 1) return r;
    else if (n % 2 != 0) return r * intPow(r, n - 1);
    else {
        double l = intPow(r, n/2);
        return l * l;
    }
}

double exp(double i){
    if (i < 0) return 1/exp(-i);
    else if (i == 0) return 1.0;
    else if (i < 1.0) {
        double result = 1.0;
        double temp = i;
        for (nat k = 1; k <= _expLim; k++) {
            result += (temp/_factorial[k]);
            temp *= i;
        }
        
        return result;
    } else {
        int I = (int)i;
        double J = i - I;
        
        return  intPow(E, I) * exp(J);
    }
}

double ln(double i) {
    if (i <= 0) {// do something // return 0;}
    else if (i == 1.0) return 0;
    else if (i < E) {
        double j = i - 1;
        double result = j;

        nat k = 1;

        // goes with Maclaurin series of ln(1+x) =
        // = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + ... 
        double temp = j * j;
        while(k < _expLim) {
            double M = alt(k) * temp; k++;
            result += (M / _factorial[k]);
            temp *= j;
        }

        return result;
    } else {
        double j = i;
        double result = 0;
        for (; j >= E; j /= E)
            result += 1.0;
        return result + ln(j); 
    }
}


double lnInt(int i) {

}


double Log(double a, double b) {
    //return Log[a](b)
    return ln(b) / ln(a);
}


double sqrtInt(int a) {
}
double sqrt(double a) {
    if (a < 0) { // do something // return 0;}
    else if (a == 0) return 0;
    else if (a == 1) return 1;
    else if (a < 2) 
        return pow(a, .5);
    
}


double pow(double r, double n) {
    int N = (int)n;
    int M = n - N;
    if (M == 0) return intPow(r, N);
    else return intPow(r, N) * exp(ln(r) * M);
}


double _sin(double theta){
    // only if theta is between 0 and PI/6
    double result = theta;

    double theta2 = theta * theta;

    double temp = theta2 * theta;

    for (nat n = 3, k = 1; n < 10; n += 2) {
        result += (alt(k++) * temp / _factorial[n]);
        temp *= theta2;
    }

    return result;
}

double _cos(double theta) {
    // only if theta is between 0 and PI/6
    double result = 1.0;

    double theta2 = theta * theta;

    double temp = theta2;

    for (nat n = 2, k = 1; n < 10; n += 2) {
        result += (alt(k++) * temp / _factorial[n]);
        temp *= theta2;
    }

    return result;
}



double cos(double theta);

double sin(double theta) {
    if (theta < 0) return - sin(-theta);
    else if (theta == 0) return 0;
    else if (theta < _specialAngles[1]) return _sin(theta);

    else {
        double phi = theta;

        while (phi >= TAU) phi -= TAU;

        for (nat i = 7; i >= 0; i--)
            if (phi >= _specialAngles[i]) {
                double alpha = phi - _specialAngles[i];
                return _specialCos[i] * sin(alpha) + _specialSin[i] * cos(alpha);
            }
    }

    // will never reach this point
    return 0;
}

double cos(double theta) {
    if (theta < 0) return cos(-theta);
    else if (theta == 0) return 1;

    else if (theta < _specialAngles[1]) return _cos(theta);

    else {
        double phi = theta;

        while (phi >= TAU) phi -= TAU;

        for (nat i = 7; i >= 0; i--)
            if (phi >= _specialAngles[i]) {
                double alpha = phi - _specialAngles[i];
                return _specialCos[i] * cos(alpha) - _specialSin[i] * sin(alpha);
            }
    }

    // will never reach this point
    return 0;
}
*/
