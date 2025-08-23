#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "MIPT.h"



void print_Unit(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin);



int main(int argc, const char * argv[]){
    test_solver();
    struct equation P = {};
    double x1 = 0, x2 = 0;
    NUM_SOL num_sol = ZERO;
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

int ReadFromFile(const char * argv, struct equation P, double * x1 , double * x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    FILE * fin = fopen(argv, "r");
    if(fin == NULL){
        perror("a");
        return 1;
    }
    NUM_SOL num_sol = ZERO;
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

void print_sol(NUM_SOL num_sol, double x1, double x2){
    switch(num_sol){
    case TWO:     // Magic num TD
        printf("Equation has 2 solutions: x1 = %lg x2 = %.100lg\n\n",x1,x2);
        break;
    case ONE:
        printf("Equation has 1 solution: x = %lg\n\n",x1);
        break;
    case ZERO:
        printf("Equation hasn't solutions\n\n");
        break;
    case INF:
        printf("Equation has Infinity solutions\n\n");
        break;
    default :
        printf("ERROR\n\n");
    }
}

void test_solver(void){
    FILE * fin = fopen("/home/pasha/p/PROJECT/Unit_Tests.txt", "r");
    struct equation P = {};
    NUM_SOL true_num_sol = ZERO;
    int i = 0;
    double x1 = 0, x2 = 0;
    while(1){

        int scanOK=fscanf(fin, "%lf%lf%lf%d", &P.a, &P.b, &P.c, (int*)&true_num_sol);
        if(scanOK < 4){
            break;
        }
        NUM_SOL num_sol = solver(P, &x1, &x2);
        print_Unit(true_num_sol, num_sol, x1, x2 , i, fin);

        i++;
    }
}
void print_Unit(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin){
    double true_x1 = 0, true_x2 = 0;
    switch(true_num_sol){
    case TWO: // magic num TD
        fscanf(fin, "%lg%lg", &true_x1, &true_x2);
        if(!(IsZero(true_x1 - x1) && IsZero(true_x2 - x2)  && IsZero(true_num_sol - num_sol))){
            printf("FALED: TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n\n", i, true_x1, true_x2, x1, x2);
        }
        else{
            printf("SUCCESS: TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n\n" , i, true_x1, true_x2, x1, x2);
        }
        break;
    case ONE:
        fscanf(fin, "%lg", &true_x1);
        if(!(IsZero(true_x1 - x1) && IsZero(true_num_sol - num_sol))){
            printf("FALED: TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n\n", i, true_x1, x1);
        }
        else{
            printf("SUCCESS: TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n\n" , i, true_x1, x1);
        }
        break;
    case ZERO:
        if(!(IsZero(true_num_sol - num_sol))){
            printf("FALED: TEST %d (should be 0 solutions) RESULT: %d solution(s)\n\n", i, num_sol);
        }
        else{
            printf("SUCCESS: TEST %d (should be 0 solutions) RESULT: 0 solutions\n\n" , i);
        }
        break;
    case INF:
        printf("ERROR\n\n");
        break;
    default :
        break;
    }

}

