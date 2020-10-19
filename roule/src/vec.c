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

#include "utils.h"
#include "vec.h"

/* Moves all the elements of `other_v` into `v`. */
void vec_append(Vec *v, Vec *other_v) {
    if ((sizeof(void *) * (v->len + other_v->len) > v->capacity))
        vec_resize(v, v->len + other_v->len, 0);

    for (unsigned int i = v->len; i < (v->len + other_v->len); i++) {
        v->ptr[i] = other_v->ptr[other_v->len - i];
        other_v->ptr[other_v->len - i] = NULL;
    }

    v->len += other_v->len;
}

/* Frees up the memory allocated by `v`. */
void vec_free(Vec *v) {
    free(v->ptr);

    v->ptr = NULL;
    v->capacity = 0;
    v->len = 0;
}

/* Returns a reference to the element at the specified `index`. */
void *vec_get(Vec *v, unsigned int index) {
    if (index > v->len - 1)
        panic("failed to access value: index out of bounds \n");

    return v->ptr[index];
}

/* Inserts an element at the specified `index`. */
void vec_insert(Vec *v, unsigned int index, void *value) {
    if ((sizeof(value) * (index + 1) > v->capacity))
        vec_resize(v, index + 1, 0);

    unsigned int i = index - 1;

    for (; i > index; i--)
        v->ptr[i] = v->ptr[i - 1]; // shift all elements to the right

    v->ptr[index] = value;
    v->len = index + 1;
}

/* Constructs a new, empty vector. */
Vec vec_new(void) {
    Vec v = {
        NULL,
        0,
        0
    };

    return v;
}

/* Removes the last element from the vector and returns it. */
void *vec_pop(Vec *v) {
    if (v->len > 0) {
        void *result = v->ptr[v->len - 1];
        v->ptr[v->len - 1] = NULL;
        v->len--;

        return result;
    }

    return NULL;
}

/* Adds an element at the end of the vector. */
void vec_push(Vec *v, void *value) {
    if ((sizeof(value) * (v->len + 1) > v->capacity)) {
        v->ptr = realloc(v->ptr, (v->capacity = sizeof(void *) * (v->len + 1)));

        if (v->ptr == NULL)
            panic("failed to re-allocate memory for 'ptr' \n");
    }

    v->ptr[v->len++] = value;
}

/* Removes the element at the specified `index`. */
void vec_remove(Vec *v, unsigned int index) {
    if (index > v->len - 1)
        panic("vec_remove(): failed to access value - index out of bounds \n");

    for (unsigned int i = index + 1; i < v->len - index; i++)
        v->ptr[i - 1] = v->ptr[i];

    v->len--;
}

/*
    Resizes the vector, extending it with each new slot set to `default_value`
    if `new_len` is greater than the current length.
*/
void vec_resize(Vec *v, unsigned int new_len, void *default_value) {
    if (new_len > v->len) {
        v->ptr = realloc(v->ptr, (v->capacity = sizeof(void *) * new_len));

        if (v->ptr == NULL)
            panic("vec_resize(): failed to re-allocate memory for 'ptr' \n");

        unsigned int i = v->len;

        for (; i < new_len; i++)
            v->ptr[i] = default_value;

        v->len = new_len;
    }
    else
        vec_truncate(v, new_len);
}

/* Replaces the element at the specified `index`, with `value`. */
void vec_set(Vec *v, unsigned int index, void *value) {
    if (index > v->len - 1)
        panic("vec_set(): failed to access value: index out of bounds \n");

    v->ptr[index] = value;
}

/* Shrinks the capacity of the vector as much as possible. */
void vec_shrink_to_fit(Vec *v) {
    v->ptr = realloc(v->ptr, (v->capacity = sizeof(void *) * v->len));

    if (v->ptr == NULL)
        panic("vec_shrink_to_fit(): failed to re-allocate memory for 'ptr' \n");
}

/* Shortens the vector. This function has no effect if `length` is greater than the current length of `v`. */
void vec_truncate(Vec *v, unsigned int new_length) {
    if (new_length < v->len) {
        for (unsigned int i = v->len; i < new_length; i++)
            v->ptr[i] = NULL;

        v->len = new_length;
    }
}

/* Creates a new vector with the specified `capacity`. */
Vec vec_with_capacity(int capacity) {
    void **ptr;

    if ((ptr = malloc(capacity)) == NULL)
        panic("vec_with_capacity(): failed to allocate memory for 'ptr' \n");

    Vec v = {
        ptr,
        capacity,
        0
    };

    return v;
}
