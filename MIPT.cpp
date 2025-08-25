#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "MIPT.h"
#include "COLORS.h"

//Make colored textj    \033[0m \033[0;32;40m       \033[0;34;40m\033[0m       \033[0;31;40mERROR\033[0m


/**
 * @brief
 *
*/

int main(int argc, const char *argv[]) {
    printf("%s\n", __TIME__);
    equation P = {};
    double x1 = 0, x2 = 0;
    NUM_SOL num_sol = SOL_ZERO;

    if (FlagFinder(argc, argv, "-t")) {
        TestSolver();
        return 0;
    }

    if (FlagFinder(argc, argv, "coefficients.txt")) {
        ReadFromFile(argv[1], P, &x1, &x2);
        return 0;
    }

    printf("Enter the mode: [m|f|u] (m - manual, f - file (default), u - unit test)\n");
    char mode = 'M';
    scanf("%c", &mode);

    switch (mode) {
    case 'm':
    case 'M':
        while(1) {
            printf("Enter the coefficients of the quadratic equation:\n");
            int scanOK = scanf("%lf%lf%lf", &P.a, &P.b, &P.c);
            if(scanOK != 3) {
                printf("%sERROR%s: Incorrect input \n\n", RED, RESET);
                break;

            }
            num_sol = Solver(P, &x1, &x2);
            PrintSol(num_sol, x1, x2);
            //buff
        }
        break;
    case 'u':
    case 'U':
        TestSolver();
        break;
    case 'f':
    default :
        if (argc < 2) {
            printf("%sERROR%s: Incorrect input \n\n", RED, RESET);
            break;
        }
        ReadFromFile(argv[1], P, &x1, &x2);
        break;
    }

    return 0;
}

int ReadFromFile(const char * argv, double * x1 , double * x2) {
    MyAssert(x1 == NULL);
    MyAssert(x2 == NULL);
    equation P = {};
    FILE * fin = fopen(argv, "r");
    if(fin == NULL) {
        perror("a");
        return 1;
    }
    NUM_SOL num_sol = SOL_ZERO;
    while(1) {
        int scanOK = fscanf(fin, "%lf%lf%lf", &P.a, &P.b, &P.c);
        if(scanOK != 3) {
            printf("%sERROR%s: Incorrect input \n\n", RED, RESET);
            break;
        }
        num_sol = Solver(P, x1, x2);
        PrintSol(num_sol, *x1, *x2);
    }
    return 0;
}
/**
    \brief

    \tparam

    \param [in] a
    \param [in] b

    \return
*/
void PrintSol(NUM_SOL num_sol, double x1, double x2) {
    switch(num_sol) {

    case SOL_TWO:
        printf("Equation has  2 solutions: x1 = %lg x2 = %lg\n",x1,x2);
        break;

    case SOL_ONE:
        printf("Equation has 1 solution: x = %lg\n",x1);
        break;

    case SOL_ZERO:
        printf("Equation has no solutions.\n");
        break;

    case SOL_INF:
        printf("Equation has an infinite number of solutions.\n");
        break;
    default :
        printf("%sERROR%s\n", RED, RESET);
    }
}


void TestSolver(void) {
    FILE * fin = fopen("Unit_Tests.txt", "r");
    equation P = {};
    NUM_SOL true_num_sol = SOL_ZERO;
    int i = 1;
    double x1 = 0, x2 = 0;
    int unit_passed = 0;
    while(1) {
        int scanOK = fscanf(fin, "%lf%lf%lf%d", &P.a, &P.b, &P.c, (int*)&true_num_sol);
        if(scanOK < 4) {
            break;
        }
        NUM_SOL num_sol = Solver(P, &x1, &x2);
        PrintUnitTestResult(true_num_sol, num_sol, x1, x2 , i, fin, &unit_passed);
        i++;
    }
    printf("Tests passed : %d / %d\n", unit_passed, i-1);

}
void PrintUnitTestResult(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin, int * unit_passed) {
    double true_x1 = 0, true_x2 = 0;
    switch(true_num_sol) {

    case SOL_TWO:
        fscanf(fin, "%lg%lg", &true_x1, &true_x2);
        if(!(IsZero(true_x1 - x1) && IsZero(true_x2 - x2)  && IsZero(true_num_sol - num_sol))) {
            printf(WordRED("FAILED") ": TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n", i, true_x1, true_x2, x1, x2);
        }
        else {
            printf("%sSUCCESS%s: TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n" , GREEN, RESET, i, true_x1, true_x2, x1, x2);
            (*unit_passed)++;
        }
        break;

    case SOL_ONE:
        fscanf(fin, "%lg", &true_x1);
        if(!(IsZero(true_x1 - x1) && IsZero(true_num_sol - num_sol))){
            printf(WordRED("FAILED")": TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n", i, true_x1, x1);
        }
        else {
            printf(WordGREEN("SUCCESS")" TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n" , i, true_x1, x1);
            (*unit_passed)++;
        }
        break;
    case SOL_ZERO:
        if(!(IsZero(true_num_sol - num_sol))) {
            printf(WordRED("FAILED")" TEST %d (should be 0 solutions) RESULT: %d solution(s)\n", i, num_sol);
        }
        else {
            printf(WordGREEN("SUCCESS")" TEST %d (should be 0 solutions) RESULT: 0 solutions\n" , i);
            (*unit_passed)++;
        }
        break;
    case SOL_INF:
        if(!(IsZero(true_num_sol - num_sol))) {
            printf(WordRED("FAILED")": TEST %d (should be infinite number of solutions) RESULT: %d solution(s)\n", i, num_sol);
        }
        else {
            printf(WordGREEN("SUCCESS") ": TEST %d (should be infinite number of solutions) RESULT: infinite number of solutions\n", i);

            (*unit_passed)++;
        }
        break;
    default :
        break;
    }

}
bool FlagFinder (int argc, const char * argv[], const char * flag) {
    for(int i = 0; i < argc; i++) {
        if (ComparisonStr(argv[i],flag)) {
            return true;
        }
    }
    return false;
}

bool ComparisonStr(const char * str1, const char * str2) {
    MyAssert(str1 == NULL);
    MyAssert(str2 == NULL);
    int j = 0;
    while((str1[j] != '\0') && (str2[j] != '\0')) {
        if (str1[j] != str2[j]) {
            return false;
        }
        j++;
    }
    return true;
}

void FindInFlagBase() {
    switch(){

    }
}

