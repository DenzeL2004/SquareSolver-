#include <stdio.h>
#include <math.h>

#include "headers\Squaref.h"
#include "headers\Testf.h"
#include "headers\Generals.h"

const int Cnt_test = 11;

const Parameters paramet[Cnt_test] =   {{1,  2,  3,  NO_ROOTS,           NAN, NAN},
                                        {1,  3,  2,    SQUARE,            -2,  -1},
                                        {1, -2,  1,  ONE_ROOT,             1, NAN},
                                        {0,  0,  0, INF_ROOTS,           NAN, NAN},
                                        {0,  0,  3,  NO_ROOTS,           NAN, NAN},
                                        {0,  4,  0,  ONE_ROOT,             0, NAN},
                                        {0,  3,  1,  ONE_ROOT, -0.3333333334, NAN},
                                        {2,  0,  0,  ONE_ROOT,             0, NAN},
                                        {3,  0,  1,  NO_ROOTS,           NAN, NAN},
                                        {1,  0, -1,    SQUARE,            -1,   1},
                                        {1,  2,  0,    SQUARE,            -2,   0}};

void unit_test(){
    int cnt_OK_tests = 0;

    for (int current_test = 0; current_test < Cnt_test; current_test++){
        double a = paramet[current_test].a,
               b = paramet[current_test].b,
               c = paramet[current_test].c;

        double x1 = NAN, x2 = NAN;
        char count_roots = 0;

        count_roots = solve_square (a, b, c, &x1, &x2);
        cnt_OK_tests += check_equality (x1, x2, count_roots, paramet[current_test], current_test+1);

        putchar ('\n');
    }

    print_colour (GREEN, "CORRECT TESTS %d\n", cnt_OK_tests);

    return;
}

int check_equality (double cur_x1, double cur_x2, char cur_count_roots, Parameters ans_param, int test_number){
    print_colour (YELLOW, "TEST NUMBER %d\n", test_number);

    int CORRECT_TEST = 1;

    print_colour (BLUE, "Input arguments:\n");
    printf ("a = %lg\nb = %lg\nc = %lg\n", ans_param.a, ans_param.b, ans_param.c);
    putchar ('\n');

    if (cur_count_roots != ans_param.count_roots){
        print_colour (RED, "FAILED:\n");

        print_colour (YELLOW, "Waiting ");
        print_result (GREEN, ans_param.count_roots);
        printf ("count roots = %d\nx1 = %lg\nx2 = %lg\n", ans_param.count_roots, ans_param.x1, ans_param.x2);

        putchar ('\n');

        print_colour (YELLOW, "Received ");
        print_result (RED, cur_count_roots);
        printf ("count roots = %d\nx1 = %lg\nx2 = %lg\n", cur_count_roots, cur_x1, cur_x2);

        return (CORRECT_TEST = 0);
    }

    switch (cur_count_roots){
        case NO_ROOTS:
            if (isnan (cur_x1) && isnan (cur_x2)){
                print_colour (GREEN, "OK not roots\n");

                return CORRECT_TEST;
            }
            else
                CORRECT_TEST = 0;

        case INF_ROOTS:
            if (isnan (cur_x1) && isnan (cur_x2)){
                print_colour (GREEN, "OK inf roots\n");

                return CORRECT_TEST;
            }
            else
                CORRECT_TEST = 0;

        case SQUARE:
            cur_x1 = fix_zero (cur_x1);
            cur_x2 = fix_zero (cur_x2);

            if (equality_double (cur_x1, ans_param.x1) && equality_double (cur_x2, ans_param.x2)){
                print_colour (GREEN, "OK two roots\n");
                printf ("x1 = %lg\nx2 = %lg\n", cur_x1, cur_x2);

                return CORRECT_TEST;
            }
            else
                CORRECT_TEST = 0;

        case ONE_ROOT:
            cur_x1 = fix_zero (cur_x1);

            if (equality_double (cur_x1, ans_param.x1) && isnan(cur_x2)){
                print_colour (GREEN, "OK one root\n");
                printf ("x = %lg\n", cur_x1);

                return CORRECT_TEST;
            }
            else
                CORRECT_TEST = 0;

        case ANOTHER: [[fallthrough]]
        default:
            print_colour (RED, "ERROR\n");
            CORRECT_TEST = 0;
    }

    if (!CORRECT_TEST){
        print_colour (RED, "WRONG\n");
        printf ("cur_x1 = %lg cur_x2 = %lg\n", cur_x1, cur_x2);
        printf ("ans_x1 = %lg ans_x2 = %lg\n", ans_param.x1, ans_param.x2);
    }

    return (CORRECT_TEST = 0);
}

void print_result (const char colour[], int count_roots){
    switch (count_roots){
        case NO_ROOTS:
            print_colour (colour, "not roots\n");
            break;

        case INF_ROOTS:
            print_colour (colour, "inf roots\n");
            break;

        case SQUARE:
            print_colour (colour, "two roots\n");
            break;

        case ONE_ROOT:
            print_colour (colour, "one roots\n");
            break;

        case ANOTHER: [[fallthrough]]
        default:
            print_colour (RED, "ERROR\n");
            break;
    }

    return;
}
