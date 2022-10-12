#include "Polynomial.h"

// Default Constructor
polynomial::polynomial() {
    head_ptr = NULL;
    many_terms = 0;
}

// Constructor with parameter as the coefficient of x^0 term.
polynomial::polynomial(node::coef_t a0) {
    if (a0 == 0) {
        head_ptr = NULL;
        many_terms = 0;
    }
    list_head_insert(head_ptr, a0, 0);
    many_terms = 1;
}

// Copy Consturctor
polynomial::polynomial(const polynomial &source) {
    node *tail_ptr;
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    many_terms = source.many_terms;
}

// Destructor
polynomial::~polynomial() {
    list_clear(head_ptr);
    many_terms = 0;
}

void polynomial::add_to_coef(node::coef_t amount, node::power_t k) {
    assert(k >= 0); // Precondition

    if (amount == 0)
        return;

    node *cursor_ptr = NULL;
    node *previous_ptr = NULL;
    node *k_exponent_ptr;

    // If there exists previous node that exponent is lesser than k,
    // previous_ptr point to the previous node. If not, previous_ptr is NULL.
    if ((head_ptr != NULL) && (head_ptr->get_exponent() < k)) {
        for (cursor_ptr = head_ptr;
             (cursor_ptr != NULL) && (cursor_ptr->get_exponent() < k);
             cursor_ptr = cursor_ptr->get_link()) {
            previous_ptr = cursor_ptr;
        }
    }

    k_exponent_ptr = list_search(head_ptr, k);
    if (k_exponent_ptr != NULL) {
        // There does not exist the node that exponent is k.
        k_exponent_ptr->set_coefficient(k_exponent_ptr->get_coefficient() +
                                        amount);

        if (k_exponent_ptr->get_coefficient() == 0) {
            // Existing coefficient plus amount is zero.
            if (previous_ptr != NULL) {
                // There exists previous node.
                list_remove(previous_ptr);
                many_terms--;
            } else {
                // There does not exist previous node.
                list_head_remove(head_ptr);
                many_terms--;
            }
        }
    } else if (previous_ptr != NULL) {
        // There exist the node that exponent is k and previous node.
        list_insert(previous_ptr, amount, k);
        many_terms++;
    } else {
        // There exists the node that exponent is k,
        // but does not exist previous node.
        list_head_insert(head_ptr, amount, k);
        many_terms++;
    }
}

void polynomial::assign_coef(node::coef_t new_coefficient, node::power_t k) {
    assert(k >= 0); // Precondition

    node *cursor_ptr = NULL;
    node *previous_ptr = NULL;
    node *k_exponent_ptr;

    // If there exists previous node that exponent is lesser than k,
    // previous_ptr point to the previous node. If not, previous_ptr is NULL.
    if ((head_ptr != NULL) && (head_ptr->get_exponent() < k)) {
        for (cursor_ptr = head_ptr;
             (cursor_ptr != NULL) && (cursor_ptr->get_exponent() < k);
             cursor_ptr = cursor_ptr->get_link()) {
            previous_ptr = cursor_ptr;
        }
    }

    k_exponent_ptr = list_search(head_ptr, k);

    if (new_coefficient == 0) {
        // Remove the node that exponent is k.
        if (k_exponent_ptr == NULL) {
            // There does not exist the node that exponent is k.
            return;
        } else {
            if (previous_ptr == NULL) {
                // There exists the node that exponent is k,
                // but does not exist previous node.
                list_head_remove(head_ptr);
                many_terms--;
            } else {
                // There exist the node that exponent is k and previous node.
                list_remove(previous_ptr);
                many_terms--;
            }
        }
    } else {
        // new_coefficient is not zero.
        if (k_exponent_ptr == NULL) {
            if (previous_ptr == NULL) {
                // All node's exponent is larger than k.
                list_head_insert(head_ptr, new_coefficient, k);
                many_terms++;
            } else {
                // There does not exist the node that exponent is k,
                // but exists previous node.
                list_insert(previous_ptr, new_coefficient, k);
                many_terms++;
            }
        } else {
            // There exists the node that exponent is k.
            k_exponent_ptr->set_coefficient(new_coefficient);
        }
    }
}

void polynomial::clear() {
    list_clear(head_ptr);
    many_terms = 0;
}

node::coef_t polynomial::coefficient_of_k(node::power_t k) const {
    assert(k >= 0); // Precondition

    node *k_exponent_ptr = list_search(head_ptr, k);
    if (k_exponent_ptr == NULL) {
        return 0;
    } else {
        return k_exponent_ptr->get_coefficient();
    }
}

node::power_t polynomial::degree() const {
    if (many_terms == 0)
        return 0; // list_locate() precondition : many_terms > 0

    node *degree_ptr = list_locate(head_ptr, many_terms);
    return degree_ptr->get_exponent();
}

node::power_t polynomial::next_term(node::power_t k) const {
    assert(k >= 0); // Precondition

    node *next_term_ptr = NULL;

    if (head_ptr != NULL) {
        for (next_term_ptr = head_ptr;
             (next_term_ptr != NULL) && (next_term_ptr->get_exponent() <= k);
             next_term_ptr = next_term_ptr->get_link()) {
        }
    }

    if (next_term_ptr == NULL) {
        return 0;
    } else {
        return next_term_ptr->get_exponent();
    }
}

node::coef_t polynomial::eval(term_t x) const {
    term_t result = 0;
    node *cursor_ptr;
    for (cursor_ptr = head_ptr; cursor_ptr != NULL;
         cursor_ptr = cursor_ptr->get_link()) {
        result +=
            cursor_ptr->get_coefficient() * pow(x, cursor_ptr->get_exponent());
    }

    return result;
}

void polynomial::show_contents() const {
    if (head_ptr == NULL)
        std::cout << "0.0";

    node *cursor_ptr;
    int terms_order = many_terms;

    std::cout << std::fixed;
    std::cout.precision(1);

    while (terms_order > 0) {
        cursor_ptr = list_locate(head_ptr, terms_order);

        if (terms_order == many_terms) {
            if (cursor_ptr->get_coefficient() < 0)
                std::cout << "- ";
            if (cursor_ptr->get_exponent() == 0) {
                std::cout << fabs(cursor_ptr->get_coefficient());
            } else if (cursor_ptr->get_exponent() == 1) {
                std::cout << fabs(cursor_ptr->get_coefficient()) << "x";
            } else {
                std::cout << fabs(cursor_ptr->get_coefficient()) << "x^"
                          << cursor_ptr->get_exponent();
            }
        } else {
            if (cursor_ptr->get_coefficient() > 0) {
                std::cout << " + ";
            } else {
                std::cout << " - ";
            }
            if (cursor_ptr->get_exponent() == 0) {
                std::cout << fabs(cursor_ptr->get_coefficient());
            } else if (cursor_ptr->get_exponent() == 1) {
                std::cout << fabs(cursor_ptr->get_coefficient()) << "x";
            } else {
                std::cout << fabs(cursor_ptr->get_coefficient()) << "x^"
                          << cursor_ptr->get_exponent();
            }
        }
        terms_order--;
    }
    std::cout << std::endl;
}

void polynomial::operator=(const polynomial &source) {
    node *tail_ptr;
    if (this == &source)
        return;
    list_clear(head_ptr);
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    many_terms = source.many_terms;
}

void polynomial::operator=(node::coef_t a0) {
    if ((many_terms == 1) && (head_ptr->get_exponent() == 0) &&
        (head_ptr->get_coefficient() == a0))
        return;
    list_clear(head_ptr);
    if (a0 == 0)
        return;
    list_head_insert(head_ptr, a0, 0);
    many_terms = 1;
}

void polynomial::operator+=(const polynomial &addend) {
    node *cursor_ptr;
    for (cursor_ptr = addend.head_ptr; cursor_ptr != NULL;
         cursor_ptr = cursor_ptr->get_link()) {
        add_to_coef(cursor_ptr->get_coefficient(), cursor_ptr->get_exponent());
    }
}

void polynomial::operator-=(const polynomial &subtrahend) {
    node *cursor_ptr;
    for (cursor_ptr = subtrahend.head_ptr; cursor_ptr != NULL;
         cursor_ptr = cursor_ptr->get_link()) {
        add_to_coef(-(cursor_ptr->get_coefficient()),
                    cursor_ptr->get_exponent());
    }
}

void polynomial::operator*=(const polynomial &factor2) {
    polynomial factor1(*this);
    node *factor1_ptr;
    node *factor2_ptr;

    clear();

    for (factor1_ptr = factor1.head_ptr; factor1_ptr != NULL;
         factor1_ptr = factor1_ptr->get_link()) {
        for (factor2_ptr = factor2.head_ptr; factor2_ptr != NULL;
             factor2_ptr = factor2_ptr->get_link()) {
            add_to_coef(
                factor1_ptr->get_coefficient() * factor2_ptr->get_coefficient(),
                factor1_ptr->get_exponent() + factor2_ptr->get_exponent());
        }
    }
}

polynomial operator+(const polynomial &p1, const polynomial &p2) {
    polynomial answer(p1);
    answer += p2;
    return answer;
}

polynomial operator-(const polynomial &p1, const polynomial &p2) {
    polynomial answer(p1);
    answer -= p2;
    return answer;
}

polynomial operator*(const polynomial &p1, const polynomial &p2) {
    polynomial answer(p1);
    answer *= p2;
    return answer;
}
