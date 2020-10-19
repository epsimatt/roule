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
#include "deque.h"
#include "utils.h"

/* Frees up the memory allocated by `dq`. */
void deque_free(Deque *dq) {
    free(dq->ptr);

    dq->ptr = NULL;
    dq->capacity = 0;
    dq->len = 0;
}

/* Removes the last element from the deque and returns it. */
void *deque_pop_back(Deque *dq) {
    if (dq->len > 0) {
        void *result = dq->ptr[dq->len - 1];
        dq->ptr[dq->len - 1] = NULL;
        dq->len--;

        return result;
    }

    return NULL;
}

/* Removes the first element from the deque and returns it. */
void *deque_pop_front(Deque *dq) {
    if (dq->len > 0) {
        void *result = dq->ptr[0];

        for (unsigned int i = 1; i < dq->len; i++)
            dq->ptr[i - 1] = dq->ptr[i];

        dq->len--;

        return result;
    }

    return NULL;
}

/* Appends an element to the back of the deque. */
void deque_push_back(Deque *dq, void *value) {
    if ((sizeof(value) * (dq->len + 1) > dq->capacity)) {
        dq->ptr = realloc(dq->ptr, (dq->capacity = sizeof(void *) * (dq->len + 1)));

        if (dq->ptr == NULL)
            panic("deque_push_back(): failed to re-allocate memory for 'ptr' \n");
    }

    dq->ptr[dq->len++] = value;
}

/* Appends an element to the front of the deque. */
void deque_push_front(Deque *dq, void *value) {
    if ((sizeof(value) * (dq->len + 1) > dq->capacity)) {
        dq->ptr = realloc(dq->ptr, (dq->capacity = sizeof(void *) * (dq->len + 1)));

        if (dq->ptr == NULL)
            panic("deque_push_front(): failed to re-allocate memory for 'ptr' \n");
    }

    for (int i = dq->len; i > 0; i--)
        dq->ptr[i] = dq->ptr[i - 1];

    dq->ptr[0] = value;
    dq->len++;
}

/* Shrinks the capacity of the deque as much as possible. */
void deque_shrink_to_fit(Deque *dq) {
    dq->ptr = realloc(dq->ptr, (dq->capacity = sizeof(void *) * dq->len));

    if (dq->ptr == NULL)
        panic("deque_shrink_to_fit(): failed to re-allocate memory for 'ptr' \n");
}

/* Creates a new deque with the specified `capacity`. */
Deque deque_with_capacity(int capacity) {
    void **ptr;

    if ((ptr = malloc(capacity)) == NULL)
        panic("deque_with_capacity(): failed to allocate memory for 'ptr' \n");

    Deque dq = {
        ptr,
        capacity,
        0
    };

    return dq;
}