#include <stdio.h>
#include <stdlib.h>

typedef enum {
    STACK_INT,
    STACK_CHAR,
    STACK_UINT64,
    STACK_FLOAT,
    STACK_STRING
} DataType;

typedef struct Stack {
    DataType type;
    size_t size;
    void *data;
    void *top;
} Stack;

Stack stackCreate(size_t size, DataType type) {
    size_t effectiveSize = 0;
    if (type == STACK_INT) {
        effectiveSize = size * sizeof(int);
    } else if (type == STACK_CHAR) {
        effectiveSize = size * sizeof(char);
    } else if (type == STACK_UINT64) {
        effectiveSize = size * sizeof(unsigned long long);
    } else if (type == STACK_FLOAT) {
        effectiveSize = size * sizeof(float);
    } else if (type == STACK_STRING) {
        effectiveSize = size * sizeof(char *);
    }

    Stack s = {
        .type = type,
        .size = size,
        .data = malloc(effectiveSize),
        .top = NULL
    }; 
}