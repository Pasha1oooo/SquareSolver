#define dx   1e-5
#define IsZero(x) (fabs((x)) <= dx)

const int INF = -1;

struct equation{
    double a = 0, b = 0 ,c = 0;
};

int test_solver(void);

int print_sol(int num_sol, double x1, double x2);



double checkRoot(struct equation P, double x);

int RootsChecker(struct equation P, double x1, double x2);

int solver(struct equation P, double * x1, double * x2);

int linearSolver(struct equation P, double * x1);

int quadraticSolver(struct equation P, double * x1 , double * x2);

int ReadFromFile(const char * argv, struct equation P, double * x1 , double * x2);
