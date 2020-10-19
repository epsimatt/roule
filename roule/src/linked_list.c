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
#include "linked_list.h"
#include "utils.h"

/* Removes all elements from the `list`. */
void linked_list_clear(LinkedList *list) {
    Node *current = list->head;

    while (list->head != NULL) {
        current = list->head;
        list->head = list->head->next;

        free(current);
    }

    list->len = 0;
    list->head = NULL;
    list->tail = NULL;
}

/* Returns `true` if `list` contains a node with `value`. */
bool linked_list_contains(LinkedList *list, int value) {
    Node *current = list->head;

    while (current != NULL) {
        if (current->value == value)
            return true;

        current = current->next;
    }

    return false;
}

/* Constructs an empty `LinkedList`. */
LinkedList linked_list_new(void) {
    LinkedList list = {
        0,
        NULL,
        NULL
    };

    return list;
}

/* Adds the `node` at the end of the `list`. */
void linked_list_push_back(LinkedList *list, Node *node) {
    /*
        [head] --- ... --- [tail] --- [ ]
                                       ^
                                       |___ [node]
    */

    node->prev = list->tail;
    node->next = NULL; // 마지막 노드이므로 다음 노드는 없음

    // 비어있는 `list`에 새로운 노드를 추가하는 경우, `list->head`와 `list->tail`은 같아야 됨!
    if (list->tail == NULL)
        list->head = node;
    else
        // [`list->tail`이 가리키는 노드]의 그 다음 노드를 `node`로 변경
        list->tail->next = node;

    // 마지막 노드 업데이트
    list->tail = node;
    list->len++;
}

/* Adds the `node` at the beginning of the `list`. */
void linked_list_push_front(LinkedList *list, Node *node) {
    /*
        [ ] --- [head] --- ... --- [tail]
         ^
         |___ [node]
    */

    node->prev = NULL; // 첫 번째 노드이므로 이전 노드는 없음
    node->next = list->head;

    if (list->head == NULL)
        list->tail = node;
    else
        // [`list->head`가 가리키는 노드]의 바로 전 노드를 `node`로 변경
        list->head->prev = node;

    // 첫 번째 노드 업데이트
    list->head = node;
    list->len++;
}

/* Constructs an empty `Node`. */
Node *node_new(int value) {
    Node *node;

    if ((node = (Node *) malloc(sizeof(Node))) == NULL)
        panic("node_new(): failed to allocate memory for 'node'");

    node->value = value;
    node->prev = NULL;
    node->next = NULL;

    return node;
}
