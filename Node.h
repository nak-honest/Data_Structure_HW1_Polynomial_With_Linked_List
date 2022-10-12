#include <cstdlib>

class node {
  public:
    typedef double coef_t;        // member variable coefficioent's type
    typedef unsigned int power_t; // member variable exponent's type

    // Constructor
    node(const coef_t &init_coefficient = coef_t(),
         const power_t &init_exponent = power_t(), node *init_link = NULL);

    // member function
    void set_coefficient(const coef_t &new_coefficient) {
        coefficient = new_coefficient;
    }
    void set_exponent(const power_t &new_exponent) { exponent = new_exponent; }
    void set_link(node *new_link) { link = new_link; }
    coef_t get_coefficient() const { return coefficient; }
    power_t get_exponent() const { return exponent; }
    node *get_link() { return link; }
    const node *get_link() const { return link; }

  private:
    coef_t coefficient;
    power_t exponent;
    node *link;
};
