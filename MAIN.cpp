#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "SOLVER.h"
#include "MyAssert.h"

#define DX   1e-5
#define IsZero(x) (fabs((x)) <= DX)



typedef enum {
    MODE_t = 1,
    MODE_f = 2,
    MODE_h = 3,
    MODE_m = 4,
    MODE_kit = 5
} FLAGS;

static void    ManualMode(void);
static FLAGS   FindInFlagBase(int argc, const char * argv[], const char ** file);
static void    ClearBuffer(void);
static void    PrintHelp(void);
static void    TestSolver(void);
static void    PrintSol(NUM_SOL num_sol, double x1, double x2);
static int     ReadFromFile(const char * argv);
static void    PrintUnitTestResult(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, char * a,  int * unit_passed, int * num, int num_r);
static int     FlagFinder(int argc, const char * argv[], const char * flag);
static bool    ComparisonStr(const char * str1, const char * str2); //strcmp
static char *    DynamicRead(FILE * fin);

int main(int argc, const char *argv[]) {
    //double DX;
    printf("%s\n", __TIME__);
    printf("MEOW\n");

    FILE * fin2 = fopen("POLTORASHKA.txt", "r");

    const char * file = NULL;
    switch(FindInFlagBase( argc, argv, &file)) {
    case MODE_kit:
        for (int i=0; i<22300;i++){
            putchar(getc(fin2));
        }
        return 0;
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
    \brief функция которая выводит корни
    \param [in] num_sol - количество решений уравнения
    \param [in] x1, x2 - корни уравнения
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

/**
    \brief функция которая запускает проверку работоспособности программы
    \brief Для её работы нужен файл "Unit_Tests.txt" с 3 коэффицентами , количеством решений и правильно решённым уравнением соответсвенно для каждого теста
*/
    //n = fread(a,sizeof(char),n,fin);

static void TestSolver(void) {
    FILE * fin = fopen("Unit_Tests.txt", "r");
    char * a = DynamicRead(fin);
    equation P = {};
    NUM_SOL true_num_sol = SOL_ZERO;
    int i = 1;
    double x1 = 0, x2 = 0;
    int unit_passed = 0;
    int num = 0;
    int num_r = 0;
    while(1) {
        i//nt .. = pfscanf(pf, "a = %d", &a)
        int scanOK = sscanf(a + num_r, "a = %lf, b = %lf, c = %lf, n = %d%n", &P.a, &P.b, &P.c, (int*)&true_num_sol, &num);
        num_r+=num;
        if(scanOK < 4) {
            break;
        }
        NUM_SOL num_sol = Solver(P, &x1, &x2);
        PrintUnitTestResult(true_num_sol, num_sol, x1, x2 , i, a, &unit_passed, &num, num_r);
        num_r+=num;
        i++;
    }
    printf("Tests passed : %d / %d\n", unit_passed, i-1);
    free(a);

}

/**
    \brief функция, которая выводит информацию о том правильно ли отработала программа
    \param [in] num_sol - количество решений уравнения
    \param [in] x1, x2 - корни уравнения
    \param [in] x1, x2 - корни уравнения
    \param [in] x1, x2 - корни уравнения
    \param [in] x1, x2 - корни уравнения
*/

static void PrintUnitTestResult(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, char * a, int * unit_passed, int * num, int num_r) {
    double true_x1 = 0, true_x2 = 0;
    switch(true_num_sol) {
    case SOL_TWO:
        //printf("%s", a);
        sscanf(a + num_r, ", x1 = %lg, x2 = %lg\n%n", &true_x1, &true_x2, num);
        if(!(IsZero(true_x1 - x1) && IsZero(true_x2 - x2)  && IsZero(true_num_sol - num_sol))) {
            printf(WordRED("FAILED") ": TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n", i, true_x1, true_x2, x1, x2);
        }
        else {
            printf(WordGREEN("SUCCESS") ": TEST %d (should be x1 = %lg x2 = %lg) RESULT: x1 = %lg x2 = %lg\n" , i, true_x1, true_x2, x1, x2);
            (*unit_passed)++;
        }
        break;

    case SOL_ONE:
        sscanf(a+ num_r, ", x1 = %lg\n%n", &true_x1, num);
        if(!(IsZero(true_x1 - x1) && IsZero(true_num_sol - num_sol))){
            printf(WordRED("FAILED")": TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n", i, true_x1, x1);
        }
        else {
            printf(WordGREEN("SUCCESS")" TEST %d (should be x1 = %lg) RESULT: x1 = %lg\n" , i, true_x1, x1);
            (*unit_passed)++;
        }
        break;
    case SOL_ZERO:
        sscanf(a+ num_r, "\n%n", num);
        if(!(IsZero(true_num_sol - num_sol))) {
            printf(WordRED("FAILED")" TEST %d (should be 0 solutions) RESULT: %d solution(s)\n", i, num_sol);
        }
        else {
            printf(WordGREEN("SUCCESS")" TEST %d (should be 0 solutions) RESULT: 0 solutions\n" , i);
            (*unit_passed)++;
        }
        break;
    case SOL_INF:
        sscanf(a+ num_r, "\n%n", num);
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
    while((str1[j] != '\0') || (str2[j] != '\0')) {
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
        if(ComparisonStr(argv[i],"--kitten")) {
            return MODE_kit;
        }
    }
    return MODE_m;
}

static void ClearBuffer(void) {
    int c = -1;
    while(c != '\n'){
        c = getchar();
    }
}

static void PrintHelp(void) {
    printf("flags :\n");
    printf("-t                  : starts unit tests\n");
    printf("-f <name of file>   : solve tests from file\n");
    printf("--help              : print information about flags\n");
    printf("--kitten              : printit koshku poltorashku\n");
}
static void ManualMode(void) {
    equation P = {};
    double x1 = 0, x2 = 0;
    NUM_SOL num_sol = SOL_ZERO;
    char mode = 'M';

    printf("Enter the mode: [m|u] (m - manual, u - unit test)\n");
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

static char * DynamicRead(FILE * fin){
    fseek(fin,0,SEEK_END);
    size_t n = (long unsigned int)ftell(fin);
    char * a = (char*)calloc(n+1,sizeof(char));
    fseek(fin,0,SEEK_SET);
    fread(a,sizeof(char),n,fin);
    return a;
}
