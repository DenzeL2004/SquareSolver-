int read_arguments (double *a, double *b, double *c);
char type (double a, double b, double c);
double discriminant (double a, double b, double c);
char square_solve (double a, double b, double c, double *x1, double *x2);
char line_solve (double a, double b, double *x);
char count_solves (double a, double b, double c, double *x1, double *x2, char *T);
void write_result (char T, double x1, double x2);