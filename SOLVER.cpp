#include <stdio.h>
#include <math.h>
#include <assert.h>
//////
#include "MIPT.h"

NUM_SOL Solver(equation P, double * x1, double * x2) {
    if (IsZero(P.a)) {
        if (IsZero(P.b)) {
            if(IsZero(P.c)) {
                return SOL_INF;
            }
            return SOL_ZERO;
        }
        return LinearSolver(P, x1);
    }
    else {
        if (IsZero(P.c)) {
            *x1 = 0;
            *x2 = (-P.b) / P.a;
            return SOL_TWO;
        }
        return QuadraticSolver(P, x1, x2);
    }
}

NUM_SOL LinearSolver(equation P, double * x) {
    *x = (-P.c) / P.b;
    return SOL_ONE;
}

NUM_SOL QuadraticSolver(equation P, double * x1 , double * x2) {
    double D = P.b * P.b - 4 * P.a * P.c;
    if (D>0) {
        *x1 = (-P.b + sqrt(D)) / (2 * P.a);
        *x2 = (-P.b - sqrt(D)) / (2 * P.a);
        return SOL_TWO;
    }
    else if (IsZero(D)) {
        *x1 = (-P.b) / (2 * P.a);
        return SOL_ONE;
    }
    else {
        return SOL_ZERO;
    }

}
