#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "MIPT.h"

int main(int argc, const char * argv[]){

    if (flag_finder(argc, argv, "-t") == 1){
        test_solver();
    }
    equation P = {};
    double x1 = 0, x2 = 0;
    NUM_SOL num_sol = ZERO;
    printf("Enter the mode: [m|f|u] (m - manual, f - file (default), u - unit test)\n");
    char mode = 'M';
    scanf("%c", &mode);
    switch (mode){
    case 'm':
    case 'M':
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
        break;
    case 'u':
    case 'U':
        test_solver();
        break;
    case 'f':
    default :
        if (argc<2){
            printf("ERROR: Incorrect input \n\n");
            break;
        }
        ReadFromFile(argv[1], P, &x1, &x2);
        break;
    }
    return 0;
}

int ReadFromFile(const char * argv, equation P, double * x1 , double * x2){
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
    case TWO:
        printf("Equation has 2 solutions: x1 = %lg x2 = %lg\n",x1,x2);
        break;
    case ONE:
        printf("Equation has 1 solution: x = %lg\n",x1);
        break;
    case ZERO:
        printf("Equation hasn't solutions\n");
        break;
    case INF:
        printf("Equation has Infinity solutions\n");
        break;
    default :
        printf("ERROR\n");
    }
}

void test_solver(void){
    FILE * fin = fopen("/home/pasha/p/PROJECT/Unit_Tests.txt", "r");
    equation P = {};
    NUM_SOL true_num_sol = ZERO;
    int i = 0;
    double x1 = 0, x2 = 0;
    int unit_passed = 0;
    while(1){
        int scanOK=fscanf(fin, "%lf%lf%lf%d", &P.a, &P.b, &P.c, (int*)&true_num_sol);
        if(scanOK < 4){
            break;
        }
        NUM_SOL num_sol = solver(P, &x1, &x2);
        print_Unit(true_num_sol, num_sol, x1, x2 , i, fin, &unit_passed);
        i++;
    }
    printf("Tests passed : %d / %d\n", unit_passed, i);

}
void print_Unit(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin, int * unit_passed){
    double true_x1 = 0, true_x2 = 0;
    switch(true_num_sol){
    case TWO:
        fscanf(fin, "%lg%lg", &true_x1, &true_x2);
        if(!(IsZero(true_x1 - x1) && IsZero(true_x2 - x2)  && IsZero(true_num_sol - num_sol))){
            printf("FALED: TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n", i, true_x1, true_x2, x1, x2);
        }
        else{
            printf("SUCCESS: TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n" , i, true_x1, true_x2, x1, x2);
            (*unit_passed)++;
        }
        break;
    case ONE:
        fscanf(fin, "%lg", &true_x1);
        if(!(IsZero(true_x1 - x1) && IsZero(true_num_sol - num_sol))){
            printf("FALED: TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n", i, true_x1, x1);
        }
        else{
            printf("SUCCESS: TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n" , i, true_x1, x1);
            (*unit_passed)++;
        }
        break;
    case ZERO:
        if(!(IsZero(true_num_sol - num_sol))){
            printf("FALED: TEST %d (should be 0 solutions) RESULT: %d solution(s)\n", i, num_sol);
        }
        else{
            printf("SUCCESS: TEST %d (should be 0 solutions) RESULT: 0 solutions\n" , i);
            (*unit_passed)++;
        }
        break;
    case INF:
        if(!(IsZero(true_num_sol - num_sol))){
            printf("FALED: TEST %d (should be Infinity solutions) RESULT: %d solution(s)\n", i, num_sol);
        }
        else{
            printf("SUCCESS: TEST %d (should be Infinity solutions) RESULT: Infinity solutions\n" , i);
            (*unit_passed)++;
        }
        break;
    default :
        break;
    }

}
int flag_finder (int argc, const char * argv[], const char * flag){
    for(int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
        if (comparison_str(argv[i],flag)==1){
            return 1;
        }
    }
    return 0;
}

int comparison_str(const char * str1, const char * str2){
    int j = 0;
    while((str1[j] != '\0') && (str2[j] != '\0')){
        if (str1[j] != str2[j]){
            return 0;
        }
        j++;
    }
    return 1;
}

