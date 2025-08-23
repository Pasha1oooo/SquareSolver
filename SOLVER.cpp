#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "MIPT.h"

NUM_SOL solver(struct equation P, double * x1, double * x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    if (IsZero(P.a)){
        if (IsZero(P.b)){
            if(IsZero(P.c)){
                return INF;
            }
            return ZERO;
        }
        return linearSolver(P, x1);
    }
    else{
        if (IsZero(P.c)){
            *x1=0;
            *x2 = (-P.b) / P.a;
            return TWO;
        }
        return quadraticSolver(P, x1, x2);
    }
}

NUM_SOL linearSolver(struct equation P, double * x){
    assert(x != NULL);
    *x = (-P.c) / P.b;
    return ONE;
}

NUM_SOL quadraticSolver(struct equation P, double * x1 , double * x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    double D = P.b * P.b - 4 * P.a * P.c;
    if (D>0){
        *x1 = (-P.b + sqrt(D)) / (2 * P.a);
        *x2 = (-P.b - sqrt(D)) / (2 * P.a);
        return TWO;
    }
    else if (IsZero(D)){
        *x1 = (-P.b) / (2 * P.a);
        return ONE;
    }
    else{
        return ZERO;
    }

}
