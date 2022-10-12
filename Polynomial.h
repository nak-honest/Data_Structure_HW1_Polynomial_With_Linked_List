#include "SinglyLinkedList.h"
#include <cmath>
#include <iostream>

/*
The polynomial class store the each term's coefficient and exponent
in singly linked list. If the x^k term is zero, there does not exist the node
that exponent is k in list. In other words, the list don't have the node
that coefficient is zero.
If singly linked list is empty, it means that polynomial don't have any terms,
and it is treated by that polynomial equal '0'.
The nodes are stored in order from smallest to largest exponent.
Also, there does not exist two separate nodes with the same exponent.
*/

class polynomial {
  public:
    typedef std::size_t size_type; // member variable many_terms type.
    typedef double term_t;         // for eval() function parameter type.

    // Default Constructor
    polynomial();

    // Constructor with parameter as the coefficient of x^0 term.
    polynomial(node::coef_t a0);

    // Copy Consturctor
    polynomial(const polynomial &source);

    // Destructor
    ~polynomial();

    // The add_to_coef() function adds the specified amount
    // to the coefficient of the x^k term.
    // Pre : k >= 0.
    // Post : The coefficient of node that exponent is k is added by amount.
    //       If amount is 0, do not anything.
    //       If existing coefficient plus amount is zero, remove that node.
    void add_to_coef(node::coef_t amount, node::power_t k);

    // The assign_coef() function sets the x^k coefficient to new_coefficient.
    // Pre : k >= 0.
    // Post : The coefficient of node that exponent is
    //       k is assigned new_coefficient. If new_coefficient is zero,
    //       remove the node that exponent is k.
    void assign_coef(node::coef_t new_coefficient, node::power_t k);

    // The clear() function sets all coefficients to zero.
    // Pre : None.
    // Post : Remove all nodes in list(equal '0').
    void clear();

    // The coefficient_of_k() function returns the coefficient of the x^k term.
    // Pre : k >= 0.
    // Post : Return the coefficient in the node that exponent is k.
    //        If there does not exist x^k term, return zero.
    node::coef_t coefficient_of_k(node::power_t k) const;

    // The degree() function returns the degree of the polynomial.
    // Pre : None.
    // Post : Return the largest exponent in list.
    //        If list is empty, return zero.
    node::power_t degree() const;

    // The next_term() function returns the exponent of the next term
    // with a nonzero coefficient after x^k.
    // Pre : k >= 0.
    // Post : Return the exponent that is larger than k.
    //        If there does not exist the node that exponent is larger than k,
    //        return zero.
    node::power_t next_term(node::power_t k) const;

    // The eval() function evaluates a polynomial at the given value of x.
    // Pre : None.
    // Post : Return the result of polynomial assigned with x.
    node::coef_t eval(term_t x) const;

    // The show_contents() function prints the polynomial with character 'x'.
    // Pre : None.
    // Post : Print the polynomial with character 'x'.
    void show_contents() const;

    // Operator Overloading
    void operator=(const polynomial &source);
    void operator=(node::coef_t a0);
    void operator+=(const polynomial &addend);
    void operator-=(const polynomial &subtrahend);
    void operator*=(const polynomial &factor2);
    friend polynomial operator+(const polynomial &p1, const polynomial &p2);
    friend polynomial operator-(const polynomial &p1, const polynomial &p2);
    friend polynomial operator*(const polynomial &p1, const polynomial &p2);

  private:
    node *head_ptr;       // The pointer that point to the head node in list.
    size_type many_terms; // The number of the nodes in list.
};
