#include <stdio.h>
#include <math.h>
#include <assert.h>
#define dx   1e-5
#define IsZero(x) (fabs((x)) <= dx)

int test_solver(void);

int print_sol(int num_sol, double x1, double x2);

double checkRoot(struct equation P, double x);

int RootsChecker(struct equation P, double x1, double x2);

int solver(struct equation P, double * x1, double * x2);

int linearSolver(struct equation P, double * x1);

int quadraticSolver(struct equation P, double * x1 , double * x2);

int ReadFromFile(const char * argv, struct equation P, double * x1 , double * x2);
===
const int INF = -1;

struct equation{
    double a = 0, b = 0 ,c = 0;
};

int main(int argc, const char * argv[]){
    test_solver();
    struct equation P = {};
    double x1 = 0, x2 = 0;
    int    num_sol = 0;
    if (argc > 1){
        ReadFromFile(argv[1], P, &x1, &x2);
    }
    while(1){
        printf("Enter the coefficients of the quadratic equation:\n");
        int scanOK = scanf("%lf%lf%lf", &P.a, &P.b, &P.c);
        if(scanOK != 3){
            printf("ERROR: Incorrect input \n\n");
            break;
        }
        num_sol = solver(P, &x1, &x2);
        print_sol(num_sol, x1, x2);
    }

    return 0;
}

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

int print_sol(int num_sol, double x1, double x2){
    switch(num_sol){
    case 2:
        printf("Equation has 2 solutions: x1 = %lg x2 = %lg\n\n",x1,x2);
        break;
    case 1:
        printf("Equation has 1 solution: x = %lg\n\n",x1);
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
    FILE * fin = fopen("/home/pasha/p/PROJECT/Unit_Tests.txt", "r");
    struct equation P;
    int i = 0;
    while(1){
        double x1 = 0, x2 = 0;
        double true_x1 = 0, true_x2 = 0;
        int scanOK=fscanf(fin, "%lf%lf%lf%lf%lf", &P.a, &P.b, &P.c, &true_x1, &true_x2);
        if(scanOK != 5){
            break;
        }
        solver(P, &x1, &x2);
        if(!(IsZero(true_x1-x1) && IsZero(true_x2-x2))){
            printf("FALED: TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n\n", i, true_x1, true_x2, x1, x2);
        }
        else{
            printf("SUCCESS: TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n\n" , i, true_x1, true_x2, x1, x2);
        }
        i++;
    }
    return 0;
}
/*
int RootsChecker(struct equation P, double x1, double x2){
    if (IsZero(checkRoot(P,x1)) && (IsZero(checkRoot(P,x2)))){
        return 1;
    }
    else{
        return 0;
    }
}

double checkRoot(struct equation P, double x){
    return P.a * x * x + P.b * x +P.c ;
}
*/////


int linearSolver(struct equation P, double * x){
    assert(x != NULL);
    *x = (-P.c) / P.b;
    return 0;
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

int ReadFromFile(const char * argv, struct equation P, double * x1 , double * x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    FILE * fin = fopen(argv, "r");
    if(fin == NULL){
        perror("a");
        return 1;
    }
    int num_sol = 0;
    while(1){
        int scanOK=fscanf(fin, "%lf%lf%lf", &P.a, &P.b, &P.c);
        if(scanOK != 3){
            printf("ERROR: Incorrect input \n\n");
            break;
        }
        num_sol = solver(P, x1, x2);
        print_sol(num_sol, *x1, *x2);
    }
    return 0;
}


