#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "SOLVER.h"
#include "MyAssert.h"

#define dx   1e-5
#define IsZero(x) (fabs((x)) <= dx)

typedef enum {
    MODE_t = 1,
    MODE_f = 2,
    MODE_h = 3,
    MODE_m = 4
} FLAGS;

static void    ManualMode(void);
static FLAGS   FindInFlagBase(int argc, const char * argv[], const char ** file);
static void    ClearBuffer(void);
static void    PrintHelp(void);
static void    TestSolver(void);
static void    PrintSol(NUM_SOL num_sol, double x1, double x2);
static int     ReadFromFile(const char * argv);
static void    PrintUnitTestResult(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin,  int * unit_passed);
static int     FlagFinder(int argc, const char * argv[], const char * flag);
static bool    ComparisonStr(const char * str1, const char * str2); //strcmp

/**
 * @brief
 *
*/

int main(int argc, const char *argv[]) {
    printf("%s\n", __TIME__);
    const char * file = NULL;
    switch(FindInFlagBase( argc, argv, &file)){
    case MODE_t:
        TestSolver();
        return 0;
    case MODE_f:
        MyAssert(file != NULL);
        ReadFromFile(file);
        return 0;
    case MODE_h:
        PrintHelp();
        return 0;
    case MODE_m:
    default :
        ManualMode();
        return 0;
    }
}

static int ReadFromFile(const char * argv) {
    equation P = {};
    double x1 = 0, x2 = 0;
    FILE * fin = fopen(argv, "r");
    if(fin == NULL) {
        perror("a");
        return 1;
    }
    NUM_SOL num_sol = SOL_ZERO;
    while(1) {
        int scanOK = fscanf(fin, "%lf%lf%lf", &P.a, &P.b, &P.c);
        if(scanOK != 3) {
            printf("" WordYELLOW(" END OF FILE ") " \n\n");
            break;
        }
        num_sol = Solver(P, &x1, &x2);
        PrintSol(num_sol, x1, x2);
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
static void PrintSol(NUM_SOL num_sol, double x1, double x2) {
    switch(num_sol) {

    case SOL_TWO:
        printf("Equation has  2 solutions: x1 = %lg x2 = %lg\n",x1,x2);
        break;

    case SOL_ONE:
        printf("Equation has 1 solution: x = %lg\n",x1);
        break;

    case SOL_ZERO:
        printf("Equation hasn't solutions\n");
        break;

    case SOL_INF:
        printf("Equation has Infinity solutions\n");
        break;
    default :
        printf("%sERROR%s\n", RED, RESET);
    }
}


static void TestSolver(void) {
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
static void PrintUnitTestResult(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin, int * unit_passed) {
    double true_x1 = 0, true_x2 = 0;
    switch(true_num_sol) {

    case SOL_TWO:
        fscanf(fin, "%lg%lg", &true_x1, &true_x2);
        if(!(IsZero(true_x1 - x1) && IsZero(true_x2 - x2)  && IsZero(true_num_sol - num_sol))) {
            printf(WordRED("FAILED") ": TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n", i, true_x1, true_x2, x1, x2);
        }
        else {
            printf(WordGREEN("SUCCESS") ": TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n" , i, true_x1, true_x2, x1, x2);
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
            printf(WordRED("FAILED")": TEST %d (should be Infinity solutions) RESULT: %d solution(s)\n", i, num_sol);
        }
        else {
            printf(WordGREEN("SUCCESS") ": TEST %d (should be Infinity solutions) RESULT: Infinity solutions\n", i);
            (*unit_passed)++;
        }
        break;
    default :
        break;
    }

}

static int FlagFinder (int argc, const char * argv[], const char * flag) {
    for(int i = 0; i < argc; i++) {
        if (ComparisonStr(argv[i],flag)) {
            return i;
        }
    }
    return 0;
}

static bool ComparisonStr(const char * str1, const char * str2) {
    MyAssert(str1 != NULL);
    MyAssert(str2 != NULL);
    int j = 0;
    while((str1[j] != '\0') && (str2[j] != '\0')) {
        if (str1[j] != str2[j]) {
            return false;
        }
        j++;
    }
    return true;
}

static FLAGS FindInFlagBase(int argc, const char * argv[], const char ** file) {
    for(int i = 0; i < argc; i++) {
        if(ComparisonStr(argv[i],"-t")) {
            return MODE_t;
        }
        if(ComparisonStr(argv[i],"-f")) {
            *file = argv[i + 1];
            return MODE_f;
        }
        if(ComparisonStr(argv[i],"--help")) {
            return MODE_h;
        }
    }
    return MODE_m;
}

static void ClearBuffer(void){
    int c = -1;
    while(c != '\n'){
        c = getchar();
    }
}

static void PrintHelp(void){
    printf("flags :\n");
    printf("-t                  : starts unit tests\n");
    printf("-f <name of file>   : solve tests from file\n");
    printf("--help              : print information about flags\n");
}
static void ManualMode(void){
    equation P = {};
    double x1 = 0, x2 = 0;
    NUM_SOL num_sol = SOL_ZERO;
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
                ClearBuffer();
            }
            break;
        case 'u':
        case 'U':
            TestSolver();
            break;

        default :
            break;
        }
}
