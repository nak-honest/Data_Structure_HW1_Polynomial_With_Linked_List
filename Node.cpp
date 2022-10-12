#include "Node.h"

// Constructor's definition
node::node(const coef_t &init_coefficient, const power_t &init_exponent,
           node *init_link) {
    coefficient = init_coefficient;
    exponent = init_exponent;
    link = init_link;
}
