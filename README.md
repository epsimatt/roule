# roule

An implementation of various data structures in C.

## Linked Lists

```c
#include <stdio.h>
#include "lib/linked_list.h"

int main(void) {
    LinkedList list = linked_list_new();

    Node *first = node_new(10);
    Node *second = node_new(20);
    Node *third = node_new(30);
    Node *fourth = node_new(40);

    linked_list_push_back(&list, second);
    linked_list_push_back(&list, third);
    linked_list_push_back(&list, fourth);

    linked_list_push_front(&list, first);

    linked_list_clear(&list);
    
    return 0;
}
```

## Queues (and Deques)

```c
#include <stdio.h>
#include "lib/queue.h"

int main(void) {
    Queue q = queue_with_capacity(sizeof(int) * 4);

    queue_push(&q, 10);
    queue_push(&q, 20);
    queue_push(&q, 30);
    queue_push(&q, 40);

    queue_free(&q);
    
    return 0;
}
```

## Stacks

```c
#include <stdio.h>
#include "lib/stack.h"

int main(void) {
    Stack s = stack_with_capacity(sizeof(int) * 4);

    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 40);
    stack_push(&s, 80);

    stack_pop(&s);

    stack_free(&s);
    
    return 0;
}
```

## Vectors

```c
#include <stdio.h>
#include "lib/vec.h"

int main(void) {
    Vec v = vec_with_capacity(sizeof(int) * 3);

    vec_push(&v, 10);
    vec_push(&v, 20);
    vec_push(&v, 40);

    vec_pop(&v);

    vec_truncate(&v, 3);

    vec_free(&v);

    return 0;
}
```
