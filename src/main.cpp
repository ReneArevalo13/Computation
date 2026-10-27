#include "calculus.hpp" // Provided automatically by your calculus library
#include "linalg.hpp"   // Provided automatically by your linear-algebra library
#include "rootfinding.hpp" // Provided automatically by your root-finding library
#include <iostream>

// A mock math function to test your algorithms on: f(x) = x^2 - 4
double my_math_function(double x) { return (x * x) / 2.0; }

int main() {
  std::cout << "=================================" << std::endl;
  std::cout << "🧮 Running Computation Engine     " << std::endl;
  std::cout << "=================================" << std::endl;

  // 1. Test your calculus library
  double integral =
      num_methods::calculus::trapezoidal_rule(my_math_function, 0.0, 2.0, 100);
  std::cout << " [Calculus] Integral result:      " << integral << std::endl;

  // 2. Test your linear algebra library
  // num_methods::linalg::solve_matrix(...);

  // 3. Test your root-finding library
  // num_methods::rootfinding::bisection(...);

  std::cout << "=================================" << std::endl;
  return 0;
}
