#pragma once
#include <string>
#include <vector>

namespace num_methods::linalg {
    using Matrix = std::vector<std::vector<double>>;
    using Vector = std::vector<double>;

    Vector gaussian_elimination(Matrix A, Vector b);
    void print_matrix(const Matrix& matrix, const std::string& label = "");
}
