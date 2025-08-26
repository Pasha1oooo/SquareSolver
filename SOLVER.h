#define dx   1e-5
#define IsZero(x) (fabs((x)) <= dx)

typedef enum {
    SOL_ZERO = 0,
    SOL_ONE = 1,
    SOL_TWO = 2,
    SOL_INF = -1
} NUM_SOL;


typedef struct {
    double a = 0, b = 0 ,c = 0;
} equation;


NUM_SOL Solver(equation P, double * x1, double * x2);
NUM_SOL LinearSolver(equation P, double * x1);
NUM_SOL QuadraticSolver(equation P, double * x1 , double * x2);
