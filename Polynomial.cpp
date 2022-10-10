#include "Polynomial.h"

polynomial::polynomial() {
	head_ptr = NULL;
	many_terms = 0;
}

polynomial::polynomial(node::coef_t a0) {
	if (a0 == 0) {
		head_ptr = NULL;
		many_terms = 0;
	}
	list_head_insert(head_ptr, a0, 0);
	many_terms = 1;
}

polynomial::polynomial(const polynomial& source) {
	node* tail_ptr;
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_terms = source.many_terms;
}

polynomial::~polynomial() {
	list_clear(head_ptr);
	many_terms = 0;
}



void polynomial::add_to_coef(node::coef_t amount, node::power_t k) {
	if (amount == 0) return;

	node* cursor_ptr = NULL;
	node* previous_ptr = NULL;
	node* k_exponent_ptr;

	if ((head_ptr != NULL) && (head_ptr->get_exponent() < k)) {
		for (cursor_ptr = head_ptr; (cursor_ptr != NULL) && (cursor_ptr->get_exponent() < k); cursor_ptr = cursor_ptr->get_link()) {
			previous_ptr = cursor_ptr;
		}
	}

	k_exponent_ptr = list_search(head_ptr, k);
	if (k_exponent_ptr != NULL) {
		k_exponent_ptr->set_coefficient(k_exponent_ptr->get_coefficient() + amount);

		if (k_exponent_ptr->get_coefficient() == 0) {
			if (previous_ptr != NULL) {
				list_remove(previous_ptr);
				many_terms--;
			} else {
				list_head_remove(head_ptr);
				many_terms--;
			}
		}
	} else if (previous_ptr != NULL) {
		list_insert(previous_ptr, amount, k);
		many_terms++;
	} else {
		list_head_insert(head_ptr, amount, k);
		many_terms++;
	}
}
 
void polynomial::assign_coef(node::coef_t new_coefficient, node::power_t k) {
	node* cursor_ptr = NULL;
	node* previous_ptr = NULL;
	node* k_exponent_ptr;

	if ((head_ptr != NULL) && (head_ptr->get_exponent() < k)) {
		for (cursor_ptr = head_ptr; (cursor_ptr != NULL) && (cursor_ptr->get_exponent() < k); cursor_ptr = cursor_ptr->get_link()) {
			previous_ptr = cursor_ptr;
		}
	}

	k_exponent_ptr = list_search(head_ptr, k);

	if (new_coefficient == 0) {
		if (k_exponent_ptr == NULL) {
			return;
		} else {
			if (previous_ptr == NULL) {
				list_head_remove(head_ptr);
				many_terms--;
			} else {
				list_remove(previous_ptr);
				many_terms--;
			}
		}
	} else {
		if (k_exponent_ptr == NULL) {
			if (previous_ptr == NULL) {
				list_head_insert(head_ptr, new_coefficient, k);
				many_terms++;
			} else {
				list_insert(previous_ptr, new_coefficient, k);
				many_terms++;
			}
		} else {
			k_exponent_ptr->set_coefficient(new_coefficient);
		}
	}
}

void polynomial::clear() {
	list_clear(head_ptr);
	many_terms = 0;
}

node::coef_t polynomial::coefficient_of_k(node::power_t k) const {
	node* k_exponent_ptr = list_search(head_ptr, k);
	if (k_exponent_ptr == NULL) {
		return 0;
	} else {
		return k_exponent_ptr->get_coefficient();
	}
}

node::power_t polynomial::degree() const {
	if (many_terms == 0) return 0;  // list_locate() precondition : many_terms > 0

	node* degree_ptr = list_locate(head_ptr, many_terms);
	return degree_ptr->get_exponent();
}

node::power_t polynomial::next_term(node::power_t k) const {
	node* next_term_ptr = NULL;

	if (head_ptr != NULL) {
		for (next_term_ptr = head_ptr; (next_term_ptr != NULL) && (next_term_ptr->get_exponent() <= k); next_term_ptr = next_term_ptr->get_link()) {}
	}

	if (next_term_ptr == NULL) {
		return 0;
	} else {
		return next_term_ptr->get_exponent();
	}
}

node::coef_t polynomial::eval(term_t x) const {
	term_t result = 0;
	node* cursor_ptr;
	for (cursor_ptr = head_ptr; cursor_ptr != NULL; cursor_ptr = cursor_ptr->get_link()) {
		result += cursor_ptr->get_coefficient() * pow(x, cursor_ptr->get_exponent());
	}

	return result;
}

void polynomial::show_contents() const {
	if (head_ptr == NULL) std::cout << "0.0";

	node* cursor_ptr;
	int terms_order = many_terms;

	std::cout << std::fixed;
	std::cout.precision(1);

	while (terms_order > 0) {
		cursor_ptr = list_locate(head_ptr, terms_order);

		if(terms_order == many_terms) {
			if (cursor_ptr->get_coefficient() < 0) std::cout << "- ";
			if (cursor_ptr->get_exponent() == 0) { std::cout << abs(cursor_ptr->get_coefficient());	}
			else if(cursor_ptr->get_exponent() == 1) { std::cout << abs(cursor_ptr->get_coefficient()) << "x"; }
			else { std::cout << abs(cursor_ptr->get_coefficient()) << "x^" << cursor_ptr->get_exponent(); }
		} else {
			if (cursor_ptr->get_coefficient() > 0) { std::cout << " + "; }
			else { std::cout << " - "; }
			if (cursor_ptr->get_exponent() == 0) { std::cout << abs(cursor_ptr->get_coefficient()); }
			else if (cursor_ptr->get_exponent() == 1) { std::cout << abs(cursor_ptr->get_coefficient()) << "x"; }
			else { std::cout << abs(cursor_ptr->get_coefficient()) << "x^" << cursor_ptr->get_exponent(); }
		}
		terms_order--;
	}
	std::cout << std::endl;
}

void polynomial::operator =(const polynomial& source) {
	node* tail_ptr;
	if (this == &source)
		return;
	list_clear(head_ptr);
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_terms = source.many_terms;
}

void polynomial::operator =(node::coef_t a0) {
	if ((many_terms == 1) && (head_ptr->get_exponent() == 0) && (head_ptr->get_coefficient() == a0))
		return;
	list_clear(head_ptr);
	if (a0 == 0) return;
	list_head_insert(head_ptr, a0, 0);
	many_terms = 1;
}

void polynomial::operator +=(const polynomial& addend) {
	node* cursor_ptr;
	for (cursor_ptr = addend.head_ptr; cursor_ptr != NULL; cursor_ptr = cursor_ptr->get_link()) {
		add_to_coef(cursor_ptr->get_coefficient(), cursor_ptr->get_exponent());
	}
}

void polynomial::operator -=(const polynomial& subtrahend) {
	node* cursor_ptr;
	for (cursor_ptr = subtrahend.head_ptr; cursor_ptr != NULL; cursor_ptr = cursor_ptr->get_link()) {
		add_to_coef(-(cursor_ptr->get_coefficient()), cursor_ptr->get_exponent());
	}
}

void polynomial::operator *=(const polynomial& factor2) {
	polynomial factor1(*this);
	node* factor1_ptr;
	node* factor2_ptr;

	clear();

	for (factor1_ptr = factor1.head_ptr; factor1_ptr != NULL; factor1_ptr = factor1_ptr->get_link()) {
		for (factor2_ptr = factor2.head_ptr; factor2_ptr != NULL; factor2_ptr = factor2_ptr->get_link()) {
			add_to_coef(factor1_ptr->get_coefficient() * factor2_ptr->get_coefficient(), factor1_ptr->get_exponent() + factor2_ptr->get_exponent());
		}
	}
}

polynomial operator +(const polynomial& p1, const polynomial& p2) {
	polynomial answer(p1);
	answer += p2;
	return answer;
}

polynomial operator -(const polynomial& p1, const polynomial& p2) {
	polynomial answer(p1);
	answer -= p2;
	return answer;
}

polynomial operator *(const polynomial& p1, const polynomial& p2) {
	polynomial answer(p1);
	answer *= p2;
	return answer;
}
