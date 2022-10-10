#include "SinglyLinkedList.h"
#include <iostream>
#include <cmath>

class polynomial {
public:
	typedef std::size_t size_type;
	typedef double term_t;

	polynomial();
	polynomial(node::coef_t a0);
	polynomial(const polynomial& source);
	~polynomial();

	void add_to_coef(node::coef_t amount, node::power_t k);
	void assign_coef(node::coef_t new_coefficient, node::power_t k);
	void clear();
	node::coef_t coefficient_of_k(node::power_t k) const;
	node::power_t degree() const;
	node::power_t next_term(node::power_t k) const;
	node::coef_t eval(term_t x) const;
	void show_contents() const;

	void operator =(const polynomial& source);
	void operator =(node::coef_t a0);
	void operator +=(const polynomial& addend);
	void operator -=(const polynomial& subtrahend);
	void operator *=(const polynomial& factor2);
	friend polynomial operator +(const polynomial& p1, const polynomial& p2);
	friend polynomial operator -(const polynomial& p1, const polynomial& p2);
	friend polynomial operator *(const polynomial& p1, const polynomial& p2);
private:
	node* head_ptr;
	size_type many_terms;
};
