#include "mathlib.h"

#include <math.h>

double Abs(double x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

// Sqrt function from asgn4.pdf from git provided by Veenstra, Srinivas, Grant - February thirteenth
double Sqrt(double x) {

    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;
    while (Abs(old - new) > EPSILON) {

        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
}

double Sin(double x) {
    double two_pi = 2.0 * M_PI;
    x = fmod(x, two_pi);

    if (x < 0) {
        x += two_pi;
    }

    double result = 0.0;
    double place = x;
    int i = 1;

    while (Abs(place) > EPSILON) {
        result += place;
        place *= -x * x / ((2 * i) * (2 * i + 1));
        i++;
    }
    return result;
}

double Cos(double x) {
    double two_pi = 2.0 * M_PI;
    x = fmod(x, two_pi);

    if (x < 0) {
        x += two_pi;
    }

    double result = 1.0;
    double place = 1.0;
    int i = 1;

    while (Abs(place) > EPSILON) {
        place *= -x * x / ((2 * i - 1) * (2 * i));
        result += place;
        i++;
    }
    return result;
}

double Tan(double x) {
    double two_pi = 2.0 * M_PI;
    x = fmod(x, two_pi);

    if (x < 0) {
        x += two_pi;
    }

    double sinX = Sin(x);
    double cosX = Cos(x);

    if (Abs(cosX) < EPSILON) {
        return 1;
    }
    return sinX / cosX;
}
