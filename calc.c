#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For getopt

bool use_libm = false; // Global flag to use math.h functions

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "mh")) != -1) {
        switch (opt) {
        case 'm': use_libm = true; break;
        case 'h': fprintf(stdout, "Usage: [options]\n"); exit(EXIT_SUCCESS);
        default: fprintf(stderr, "Invalid option. Use -h for help.\n"); exit(EXIT_FAILURE);
        }
    }

    char input[1024];
    const char *delimiters = " \n";

    while (true) {
        fprintf(stderr, "> ");
        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = 0;

        char *saveptr;
        bool error_spot = false;
        for (char *token = strtok_r(input, delimiters, &saveptr); token != NULL && !error_spot;
             token = strtok_r(NULL, delimiters, &saveptr)) {
            double number;
            if (parse_double(token, &number)) {
                if (!stack_push(number)) {
                    fprintf(stderr, ERROR_NO_SPACE, number);
                    error_spot = true;
                }
            } else if (strlen(token) == 1) {
                unary_operator_fn uop = use_libm ? libm_unary_operators[(unsigned char) *token]
                                                 : my_unary_operators[(unsigned char) *token];
                binary_operator_fn op = binary_operators[(unsigned char) *token];
                if (uop != NULL) {
                    if (!apply_unary_operator(uop)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error_spot = true;
                    }
                } else if (op != NULL) {
                    if (!apply_binary_operator(op)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error_spot = true;
                    }
                } else {
                    fprintf(stderr, ERROR_BAD_CHAR, *token);
                    error_spot = true;
                }
            } else {
                fprintf(stderr, ERROR_BAD_STRING, token);
                error_spot = true;
            }
        }
        if (!error_spot) {
            stack_print();
            printf("\n");
        }
        stack_clear();
    }
    return 0;
}
