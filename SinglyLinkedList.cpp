#include "SinglyLinkedList.h"

size_t list_length(const node *head_ptr) {
    size_t answer = 0;
    const node *cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->get_link())
        ++answer;
    return answer;
}

node *list_search(node *head_ptr, const node::power_t &exponent_target) {
    node *cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->get_link())
        if (exponent_target == cursor->get_exponent())
            return cursor;
    return NULL;
}

const node *list_search(const node *head_ptr,
                        const node::power_t &exponent_target) {
    const node *cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->get_link())
        if (exponent_target == cursor->get_exponent())
            return cursor;
    return NULL;
}

node *list_locate(node *head_ptr, size_t position) {
    assert(0 < position); // Precondition.

    node *cursor = head_ptr;
    size_t i;
    for (i = 1; (cursor != NULL && i < position); ++i)
        cursor = cursor->get_link();
    return cursor;
}

const node *list_locate(const node *head_ptr, size_t position) {
    assert(0 < position); // Precondition.

    const node *cursor = head_ptr;
    size_t i;
    for (i = 1; (cursor != NULL && i < position); ++i)
        cursor = cursor->get_link();
    return cursor;
}

void list_insert(node *previous_ptr, const node::coef_t &new_coefficient,
                 const node::power_t &new_exponent) {
    assert(previous_ptr != NULL); // Precondition

    previous_ptr->set_link(
        new node(new_coefficient, new_exponent, previous_ptr->get_link()));
}

void list_head_insert(node *&head_ptr, const node::coef_t &new_coefficient,
                      const node::power_t &new_exponent) {
    head_ptr = new node(new_coefficient, new_exponent, head_ptr);
}

void list_head_remove(node *&head_ptr) {
    if (head_ptr == NULL) // List is empty.
        return;
    node *remove_ptr;
    remove_ptr = head_ptr;
    head_ptr = head_ptr->get_link();
    delete remove_ptr;
}

void list_remove(node *previous_ptr) {
    assert(previous_ptr != NULL); // Precondition.

    node *remove_ptr;
    remove_ptr = previous_ptr->get_link();
    previous_ptr->set_link(remove_ptr->get_link());
    delete remove_ptr;
}

void list_clear(node *&head_ptr) {
    while (head_ptr != NULL)
        list_head_remove(head_ptr);
}

void list_copy(const node *source_ptr, node *&head_ptr, node *&tail_ptr) {
    head_ptr = NULL;
    tail_ptr = NULL;
    if (source_ptr == NULL) // Source list is empty.
        return;
    list_head_insert(head_ptr, source_ptr->get_coefficient(),
                     source_ptr->get_exponent()); // deep copy the head node.
    tail_ptr = head_ptr;
    source_ptr = source_ptr->get_link();
    while (source_ptr != NULL) { // deep copy all nodes behind head node.
        list_insert(tail_ptr, source_ptr->get_coefficient(),
                    source_ptr->get_exponent());
        tail_ptr = tail_ptr->get_link();
        source_ptr = source_ptr->get_link();
    }
}
