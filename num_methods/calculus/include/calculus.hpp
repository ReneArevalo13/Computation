#pragma once

namespace num_methods::calculus {
// A simple trapezoidal integration algorithm example
double trapezoidal_rule(double (*func)(double), double a, double b, int n);
} // namespace num_methods::calculus
