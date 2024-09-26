#include "mathlib.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

void testMathFunctions(void) {

    assert(Abs(-10) == 10);
    assert(Abs(10) == 10);

    assert(Sqrt(4) == 2);
    assert(Sqrt(9) == 3);

    assert(fabs(Sin(0) - 0) < EPSILON);
    assert(fabs(Sin(M_PI / 2) - 1) < EPSILON);
    assert(fabs(Cos(0) - 1) < EPSILON);
    assert(fabs(Cos(M_PI) + 1) < EPSILON);
    assert(fabs(Tan(0) - 0) < EPSILON);
}

void testOperatorFunctions(void) {

    stack_clear();

    stack_push(1);
    stack_push(2);
    assert(apply_binary_operator(operator_add));
    assert(fabs(stack[0] - 3) < EPSILON);

    stack_clear();
    stack_push(5);
    stack_push(3);
    assert(apply_binary_operator(operator_sub));
    assert(fabs(stack[0] - 2) < EPSILON);

    stack_clear();
    stack_push(4);
    stack_push(5);
    assert(apply_binary_operator(operator_mul));
    assert(fabs(stack[0] - 20) < EPSILON);

    stack_clear();
    stack_push(20);
    stack_push(4);
    assert(apply_binary_operator(operator_div));
    assert(fabs(stack[0] - 5) < EPSILON);
}

void testStackFunctions(void) {
    double item;

    stack_clear();
    stack_push(3.14);
    assert(stack_pop(&item) && fabs(item - 3.14) < EPSILON);

    stack_clear();
    stack_push(2.718);
    assert(stack_peek(&item) && fabs(item - 2.718) < EPSILON);

    stack_clear();
    assert(stack_size == 0);
}

void testParseDouble(void) {
    double num;
    assert(parse_double("3.14", &num) && fabs(num - 3.14) < EPSILON);
    assert(!parse_double("abc", &num));
}

int main() {
    testMathFunctions();
    testOperatorFunctions();
    testStackFunctions();
    testParseDouble();
    return 0;
}
