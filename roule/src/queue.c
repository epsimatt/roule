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
#include "queue.h"
#include "utils.h"

/* Returns the last element of `q`. */
void *queue_back(Queue *q) {
    if (q->len > 0)
        return q->ptr[q->len - 1];
    else
        return NULL;
}

/* Frees up the memory allocated by `q`. */
void queue_free(Queue *q) {
    free(q->ptr);

    q->ptr = NULL;
    q->capacity = 0;
    q->len = 0;
}

/* Constructs a new, empty queue. */
Queue queue_new() {
    Queue q = {
        NULL,
        0,
        0
    };

    return q;
}

/* Returns the first element of `q`. */
void *queue_front(Queue *q) {
    if (q->len > 0)
        return q->ptr[0];
    else
        return NULL;
}

/* Removes the first element from `q` and returns it. */
void *queue_pop(Queue *q) {
    if (q->len > 0) {
        void *result = q->ptr[0];

        // 모든 원소를 한 칸씩 왼쪽으로 옮긴다.
        for (unsigned int i = 1; i < q->len; i++)
            q->ptr[i - 1] = q->ptr[i];

        q->ptr[q->len - 1] = NULL;
        q->len--;

        return result;
    }

    return NULL;
}

/* Appends an element to the back of `q`. */
void queue_push(Queue *q, void *value) {
    if ((sizeof(value) * (q->len + 1) > q->capacity)) {
        q->ptr = realloc(q->ptr, (q->capacity = sizeof(void *) * (q->len + 1)));

        if (q->ptr == NULL)
            panic("queue_push(): failed to re-allocate memory for 'ptr' \n");
    }

    q->ptr[q->len++] = value;
}

/* Creates a new queue with the specified `capacity`. */
Queue queue_with_capacity(int capacity) {
    void **ptr;

    if ((ptr = malloc(capacity)) == NULL)
        panic("queue_with_capacity(): failed to allocate memory for 'ptr' \n");

    Queue q = {
        ptr,
        capacity,
        0
    };

    return q;
}