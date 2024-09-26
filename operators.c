#include "operators.h"

#include "stack.h"

#include <assert.h>
#include <stdlib.h>

bool apply_binary_operator(binary_operator_fn op) {
    if (stack_size < 2) {
        return false;
    }

    double rhs, lhs;
    assert(stack_pop(&rhs) && stack_pop(&lhs));

    double result = op(lhs, rhs);
    stack_push(result);

    return true;
}

// apply_unary_operator function from asgn4.pdf from git provided by Veenstra, Srinivas, Grant - February thirteenth
bool apply_unary_operator(unary_operator_fn op) {

    if (stack_size < 1) {
        return false;
    }
    double x;

    assert(stack_pop(&x));

    double result = op(x);

    assert(stack_push(result));

    return true;
}

double operator_add(double lhs, double rhs) {
    double add_result = lhs + rhs;
    return add_result;
}

double operator_sub(double lhs, double rhs) {
    double sub_result = lhs - rhs;
    return sub_result;
}

double operator_mul(double lhs, double rhs) {
    double mul_result = lhs * rhs;
    return mul_result;
}

double operator_div(double lhs, double rhs) {
    double div_result = lhs / rhs;
    return div_result;
}

// parse_double function from asgn4.pdf from git provided by Veenstra, Srinivas, Grant - February thirteenth
bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {

        *d = result;
        return true;
    } else {
        return false;
    }
}
