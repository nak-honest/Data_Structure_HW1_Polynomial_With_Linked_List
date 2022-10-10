#include "Node.h"
#include <cassert>

size_t list_length(const node* head_ptr);
node* list_search(node* head_ptr, const node::power_t& exponent_target);
const node* list_search(const node* head_ptr, const node::power_t& exponent_target);
node* list_locate(node* head_ptr, size_t position);
const node* list_locate(const node* head_ptr, size_t position);
void list_insert(node* previous_ptr, const node::coef_t& new_coefficient, const node::power_t& new_exponent);
void list_head_insert(node*& head_ptr, const node::coef_t& new_coefficient, const node::power_t& new_exponent);
void list_head_remove(node*& head_ptr);
void list_remove(node* previous_ptr);
void list_clear(node*& head_ptr);
void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr);
