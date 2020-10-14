#include "graphing.h"
#include <math.h>

//SENOIDE MALUCA

/*
float a1 = -1.4;
float a2 = 10;
float a3 = 3.4;
float a4 = -10;

float A = 4.2;
float B = -7;
float C = 8;
float D = -10;

double pi = 3.1415926535;
double e = 2.71828182846;

float ln(float x) { return log(x)/log(e); }
float g(float x) { return x + 200; }
float f(float x) { return ln(x); }
float s(float x) { return a1 * sin(A * pi * f(x)) + a2 * cos (B * pi * f(x)) + a3 * sin(C * pi * f(x)) + a4 * cos(D * pi * f(x)); }

float graphing::plot(float x) {
    return 0.5 * abs(50 * s(x) + 300);
}
*/

float graphing::plot(float x) {
    if (x < 100) return (x * x)/100;
    if (x < 200) return 281 + x; 
    if (x < 610.5) return x/10.f;
    if (x < 650) return abs(x-600) / (x-610);
    if (x > 900 && x < 910) return 900;
    return x*sin(x/100)/2.7;
}