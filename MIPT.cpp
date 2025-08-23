#include <stdio.h>
#include <math.h>
#include <assert.h>
#define dx   1e-5
#define NearZero(x) (fabs((x)) <= dx)

// TODO: assert
// unittests
// x(x+2)
//square lineal
//const double dx  = 1e-5;

const int    INF = -1;

struct equation{
    double a = 0, b = 0 ,c = 0;
};

int test_solver(void);

int solver(struct equation P, double * x1, double * x2);

int print_sol(int num_sol, double x1, double x2);

int main(int argc, const char * argv[]){
    test_solver();
    struct equation P = {};
    double x1 = 0, x2 = 0;
    int    num_sol = 0;

    if (argc > 1){

        FILE * fin = fopen(argv[1], "r");
        if(fin == NULL){
            perror("a");
            return 1;
        }
        //while(1){
        //
        //}
        fscanf(fin, "%lf%lf%lf", &P.a, &P.b, &P.c);
        num_sol = solver(P, &x1, &x2);
        print_sol(num_sol, x1, x2);
        return 0;
    }

    while(1){
        printf("Enter the coefficients of the quadratic equation:\n");
        int scanOK = scanf("%lf%lf%lf", &P.a, &P.b, &P.c);
        if(scanOK != 3){
            printf("ERROR: Incorrect input \n\n");
            break;
        }
        num_sol=solver(P, &x1, &x2);
        print_sol(num_sol, x1, x2);
    }

    return 0;
}

int solver(struct equation P, double * x1, double * x2){
    assert(x1!=0);
    assert(x2!=0);
    if (NearZero(P.a)){
        if (NearZero(P.b)){
            if(NearZero(P.c)){
                return INF;
            }
            return 0;
        }
        *x1 = (-P.c) / P.b;
        return 1;
    }
    else{
        double D = P.b * P.b - 4 * P.a * P.c;
        if (D>0){
            *x1 = (-P.b + sqrt(D)) / (2 * P.a);
            *x2 = (-P.b - sqrt(D)) / (2 * P.a);
            return 2;
        }
        else if (NearZero(D)){
            *x1 = (-P.b) / (2 * P.a);
            return 1;
        }
        else{
            return 0;
        }
    }
}

int print_sol(int num_sol, double x1,double x2){
    switch(num_sol){
    case 2:
        printf("Equation has 2 solutions: x1=%lg x2=%lg\n\n",x1,x2);
        break;
    case 1:
        printf("Equation has 1 solution: x=%lg\n\n",x1);
        break;
    case 0:
        printf("Equation hasn't solutions\n\n");
        break;
    case INF:
        printf("Equation has Infinity solutions\n\n");
        break;
    default :
        printf("ERROR\n\n");
    }
    return 0;
}

int test_solver(void){
    struct equation P = {1, -5, 6};
    double x1 = 0, x2 = 0;
    int num_sol = solver(P, &x1, &x2);
    if (!(num_sol==2 && NearZero(x1-3) && NearZero(x2-2))){
        printf("FALED: (should be x1=3 x2=2) RESULT: x1=%lg x2=%lg\n\n",x1,x2);
    }
    else{
        printf("SUCCESS: (should be x1=3 x2=2) RESULT: x1=%lg x2=%lg\n\n",x1,x2);
    }
    return 0;
}
