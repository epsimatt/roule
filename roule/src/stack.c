/*
    Copyright (c) 2020 jdeokkim

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include "stack.h"
#include "utils.h"

/* Frees up the memory allocated by `s`. */
void stack_free(Stack *s) {
    free(s->ptr);

    s->ptr = NULL;
    s->capacity = 0;
    s->len = 0;
}

/* Constructs a new, empty stack. */
Stack stack_new() {
    Stack s = {
        NULL,
        0,
        0
    };

    return s;
}

/* Returns the last element of the stack without removing it from the stack. */
void *stack_peek(Stack *s) {
    if (s->len <= 0)
        panic("stack_peek(): failed to peek from `s` - the stack is empty! \n");

    return s->ptr[s->len - 1];
}

/* Removes the last element from the stack and returns it. */
void *stack_pop(Stack *s) {
    if (s->len > 0) {
        void *result = s->ptr[s->len - 1];
        s->ptr[s->len - 1] = NULL;
        s->len--;

        return result;
    }

    return NULL;
}

/* Adds an element at the end of the stack. */
void stack_push(Stack *s, void *value) {
    if ((sizeof(value) * (s->len + 1) > s->capacity)) {
        s->ptr = realloc(s->ptr, (s->capacity = sizeof(void *) * (s->len + 1)));

        if (s->ptr == NULL)
            panic("stack_push(): failed to re-allocate memory for 'ptr' \n");
    }

    s->ptr[s->len++] = value;
}

/* Creates a new stack with the specified `capacity`. */
Stack stack_with_capacity(int capacity) {
    void **ptr;

    if ((ptr = malloc(capacity)) == NULL)
        panic("stack_with_capacity(): failed to allocate memory for 'ptr' \n");

    Stack s = {
        ptr,
        capacity,
        0
    };

    return s;
}