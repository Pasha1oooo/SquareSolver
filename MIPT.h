#define dx   1e-5
#define IsZero(x) (fabs((x)) <= dx)

typedef enum NUM_SOL{
    ZERO = 0,
    ONE = 1,
    TWO = 2,
    INF = -1
} NUM_SOL;

typedef struct equation{
    double a = 0, b = 0 ,c = 0;
}equation;

void    TestSolver(void);
void    PrintSol(NUM_SOL num_sol, double x1, double x2);
double  checkRoot(equation P, double x);
int     RootsChecker(equation P, double x1, double x2);
NUM_SOL Solver(equation P, double * x1, double * x2);
NUM_SOL linearSolver(equation P, double * x1);
NUM_SOL QuadraticSolver(equation P, double * x1 , double * x2);
int     ReadFromFile(const char * argv, equation P, double * x1 , double * x2);
void    PrintUnit(NUM_SOL true_num_sol, NUM_SOL num_sol, double x1, double x2, int i, FILE * fin,  int * unit_passed);
NUM_SOL FlagFinder(int argc, const char * argv[], const char * flag);
NUM_SOL ComparisonStr(const char * str1, const char * str2); //strcmp

