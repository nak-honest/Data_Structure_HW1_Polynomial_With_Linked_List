#include "Polynomial.h"
using namespace std;

int main() {
	polynomial p1; // Empty list is "0", p1 = 0.0
	cout << "p1 = ";
	p1.show_contents();

	polynomial p2(-5); //p2 = - 5.0
	cout << "p2 = ";
	p2.show_contents();

	p1.add_to_coef(4.5, 1); // p1 = 4.5x
	p1.add_to_coef(3.2, 3); // p1 = 3.2x^3
	p1.add_to_coef(-2, 0); // p1 = 3.2x^3 + 4.5x - 2.0
	cout << "p1 = ";
	p1.show_contents();

	polynomial p3(p1); // copy constructor, p3 = 3.2x^3 + 4.5x - 2.0
	cout << "p3 = ";
	p3.show_contents();

	p3.add_to_coef(-3.2, 3); // p3 = 4.5x - 2.0
	p3.assign_coef(2.4, 2); // p3 = 2.4x^2 + 4.5x - 2.0
	p3.assign_coef(0, 0); // p3 = 2.4x^2 + 4.5x
	cout << "p3 = ";
	p3.show_contents();

	p3.clear(); // p3 = 0.0
	cout << "p3 = ";
	p3.show_contents();

	p2.add_to_coef(-3.2, 3); // p2 = - 3.2x^3 - 5.0
	p2.add_to_coef(2, 2); // p2 = - 3.2x^3 +2.0x^2 - 5.0

	/* p1 = 3.2x^3 + 4.5x - 2.0,   p2 = - 3.2x^3 + 2.0x^2 - 5.0,   p3 = 0.0 */
	cout << "the coefficient of x^3 in p1 = " << p1.coefficient_of_k(3) << endl; // 3.2
	cout << "the coefficient of x^4 in p1 = " << p1.coefficient_of_k(4) << endl; // 0.0
	cout << "the degree of p1 = " << p1.degree() << endl; // 3
	cout << "the degree of p3 = " << p3.degree() << endl; // 0
	cout << "the next term of x^0 of p1 = " << p1.next_term(0) << endl; // 1
	cout << "the next term of x^2 of p1 = " << p1.next_term(2) << endl; // 3
	cout << "the next term of x^1 of p3 = " << p3.next_term(1) << endl; // 0, there is not next term of x
	cout << "the result of p1 when x is 1.5 = " << p1.eval(1.5) << endl; // 3.2 * (1.5)^3 + 4.5 * 1.5 - 2.0 = 15.6
	cout << "the result of p1 when x is 0 = " << p1.eval(0) << endl; // 3.2 * 0^3 + 4.5 * 0 - 2.0 = -2.0
	cout << "the result of p3 when x is 0 = " << p3.eval(5) << endl; // 0.0

	polynomial p4 = p1 + p2; // p4 = 3.2x^3 + 4.5x - 2.0 - 3.2x^3 + 2.0x^2 - 5.0 = 2.0x^2 + 4.5x -7.0
	cout << "p4 = p1 + p2 = ";
	p4.show_contents();

	p4 = p1 + p3; // p4 = 3.2x^3 + 4.5x - 2.0 + 0.0 = 3.2x^3 + 4.5x - 2.0
	cout << "p4 = p1 + p3 = ";
	p4.show_contents();

	p4 = p1 - p2; // p4 = 3.2x^3 + 4.5x - 2.0 - (- 3.2x^3 + 2.0x^2 - 5.0) = 6.4x^3 - 2.0x^2 + 4.5x + 3.0
	cout << "p4 = p1 - p2 = ";
	p4.show_contents();

	p4 = p1 - p3; // p4 = 3.2x^3 + 4.5x - 2.0 - 0.0 = 3.2x^3 + 4.5x - 2.0
	cout << "p4 = p1 - p3 = ";
	p4.show_contents();

	p4 = p3 - p1; // p4 = 0.0 - (3.2x^3 + 4.5x - 2.0) = - 3.2x^3 - 4.5x + 2.0
	cout << "p4 = p3 - p1 = ";
	p4.show_contents();

	p4 = p1 * p2; // p4 = (3.2x^3 + 4.5x - 2.0) * (- 3.2x^3 + 2.0x^2 - 5.0) 
                          // = - 10.2x^6 + 6.4x^5 - 14.4x^4 - 0.6x^3 - 4.0x^2 - 22.5x + 10.0
	cout << "p4 = p1 * p2 = ";
	p4.show_contents();

	p4 = p1 * p3; // p4 = (3.2x^3 + 4.5x - 2.0) * 0.0 = 0.0
	cout << "p4 = p1 * p3 = ";
	p4.show_contents();

	p4 = 7.2; // p4 = 7.2
	cout << "p4 = ";
	p4.show_contents();

	p4 += p1; // p4 = 7.2 + 3.2x^3 + 4.5x - 2.0 = 3.2x^3 + 4.5x + 5.2
	cout << "p4 += p1 = ";
	p4.show_contents();

	p4 += p3; // p4 = 3.2x^3 + 4.5x + 5.2 + 0.0 = 3.2x^3 + 4.5x + 5.2
	cout << "p4 += p3 = ";
	p4.show_contents();

	p4 -= p2; // p4 = 3.2x^3 + 4.5x + 5.2 - (- 3.2x^3 + 2.0x^2 - 5.0) = 6.4x^3 - 2.0x^2 + 4.5x + 10.2
	cout << "p4 -= p2 = ";
	p4.show_contents();

	p4 -= p3; // p4 = 6.4x^3 - 2.0x^2 + 4.5x + 10.2 - 0.0 = 6.4x^3 - 2.0x^2 + 4.5x + 10.2
	cout << "p4 -= p3 = ";
	p4.show_contents();

	p4 *= p1; // p4 = (6.4x^3 - 2.0x^2 + 4.5x + 10.2) * (3.2x^3 + 4.5x - 2.0)
					// = 20.5x^6 - 6.4x^5 + 43.2x^4 + 10.8x^3 + 24.2x^2 + 36.9x - 20.4
	cout << "p4 *= p1 = ";
	p4.show_contents();

	p4 *= p3; // p4 = (20.5x^6 - 6.4x^5 + 43.2x^4 + 10.8x^3 + 24.2x^2 + 36.9x - 20.4) * 0.0 = 0.0
	cout << "p4 *= p3 = ";
	p4.show_contents();

	system("pause");
	return 0;
}
