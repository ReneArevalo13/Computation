#pragma once
#include <string>
#include <vector>

namespace num_methods::linalg {
    using Matrix = std::vector<std::vector<double>>;
    using Vector = std::vector<double>;

    // LU Decomposition
    struct LU_decomp {
        Matrix lu;    // stores LU Decomposition into a single matrix. L below diagonal, U above diagonal
        std::vector<int> pivots;    // tracks the permutations due to partial pivoting
    };

    LU_decomp lu_factorize(Matrix A);
    Vector lu_solve(const LU_decomp& factorized, const Vector& b);

    // Gausiian Elimination
    Vector gaussian_elimination(Matrix A, Vector b);
    // Print Matrix
    void print_matrix(const Matrix& matrix, const std::string& label = "");
}
