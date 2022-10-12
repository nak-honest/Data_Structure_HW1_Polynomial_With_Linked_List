#include "Node.h"
#include <cassert>

/* In all functions that have parameter as head_ptr, head_ptr is pointer of
 * list's head node. If list is empty, head_ptr is NULL. */

// The list_length() function returns the length of list
// Pre : None.
// Post : Number of nodes in list is returned.
size_t list_length(const node *head_ptr);

// The list_search() function returns the pointer of node that exponent is
// exponent_target. There are two list_search() functions,
// first can change returned node's member variables and second can't change.
// Pre : None.
// Post : Pointer of node that exponent is exponent_target is returned.
//        If there is not exist that node or list is empty, NULL is returned.
node *list_search(node *head_ptr, const node::power_t &exponent_target);
const node *list_search(const node *head_ptr,
                        const node::power_t &exponent_target);

// The list_locate() function returns the pointer of node that order is position
// in list. There are two list_locate() functions,
// first can change returned node's member variables and second can't change.
// Pre : position > 0.
// Post : Pointer of node that order is position is returned.
//        If there is not exist that node or list is empty, NULL is returned.
node *list_locate(node *head_ptr, size_t position);
const node *list_locate(const node *head_ptr, size_t position);

// The list_insert() function inserts the node behind the node
// that previous_ptr point to. That node's coefficient is new_coefficient and
// exponent is new_exponent. If you want to insert the node front the head node,
// use list_head_insert() function.
// Pre : previous_ptr is not NULL.
// Post : The node is inserted behind the node that previous_ptr point to.
void list_insert(node *previous_ptr, const node::coef_t &new_coefficient,
                 const node::power_t &new_exponent);

// The list_head_insert() function inserts the node front the head node.
// That node's coefficient is new_coefficient and exponent is new_exponent.
// Pre : None.
// Post : The node is inserted front the head node
//        and head_ptr point to this node.
void list_head_insert(node *&head_ptr, const node::coef_t &new_coefficient,
                      const node::power_t &new_exponent);

// The list_head_remove() function removes the head node.
// Pre : None.
// Post : The head node is removed and head_ptr point to the next node.
//        If the list is empty, do not anything.
void list_head_remove(node *&head_ptr);

// The list_remove() function removes the node behind the node
// that previous_ptr point to.
// Pre : previous_ptr is not NULL.
// Post : The node is removed behind the node that previous_ptr point to.
void list_remove(node *previous_ptr);

// The list_clear() function removes all nodes in list.
// Pre : None.
// Post : List is empty. head_ptr is NULL.
void list_clear(node *&head_ptr);

// The list_copy() function copys(deep copy) the list.
// Pre : None.
// Post : head_ptr point to the head node
//        in the list that is copied from source_ptr.
//        If source_ptr is NONE, then head_ptr is NONE.
void list_copy(const node *source_ptr, node *&head_ptr, node *&tail_ptr);
