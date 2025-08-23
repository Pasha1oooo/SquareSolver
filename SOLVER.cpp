#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "MIPT.h"

int solver(struct equation P, double * x1, double * x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    if (IsZero(P.a)){
        if (IsZero(P.b)){
            if(IsZero(P.c)){
                return INF;
            }
            return 0;
        }
        return linearSolver(P, x1);
    }
    else{
        if (IsZero(P.c)){
            *x1=0;
            return 1+linearSolver(P, x2);
        }
        return quadraticSolver(P, x1, x2);
    }
}

int linearSolver(struct equation P, double * x){
    assert(x != NULL);
    *x = (-P.c) / P.b;
    return 1;
}

int quadraticSolver(struct equation P, double * x1 , double * x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    double D = P.b * P.b - 4 * P.a * P.c;
    if (D>0){
        *x1 = (-P.b + sqrt(D)) / (2 * P.a);
        *x2 = (-P.b - sqrt(D)) / (2 * P.a);
        return 2;
    }
    else if (IsZero(D)){
        *x1 = (-P.b) / (2 * P.a);
        return 1;
    }
    else{
        return 0;
    }

}
