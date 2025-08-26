
#include "COLORS.h"
#ifndef MIPT_H
#define MIPT_H

#define dx   1e-5
#define IsZero(x) (fabs((x)) <= dx)
#define MyAssert(ARG) if(ARG){  printf("%s " WordRED("ERROR") ":" #ARG " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);   abort();}
#endif
typedef enum {
    SOL_ZERO = 0,
    SOL_ONE = 1,
    SOL_TWO = 2,
    SOL_INF = -1
} NUM_SOL;

typedef struct {
    double a = 0, b = 0 ,c = 0;
} equation;

void    FindInFlagBase(int argc, const char * argv[]);
void    TestSolver(void);
void    PrintSol(NUM_SOL num_sol, double x1, double x2);
NUM_SOL Solver(equation P, double * x1, double * x2);
NUM_SOL LinearSolver(equation P, double * x1);
NUM_SOL QuadraticSolver(equation P, double * x1 , double * x2);
int     ReadFromFile(const char * argv, double * x1 , double * x2);
void    PrintUnitTestResult(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin,  int * unit_passed);
bool    FlagFinder(int argc, const char * argv[], const char * flag);
bool    ComparisonStr(const char * str1, const char * str2); //strcmp


