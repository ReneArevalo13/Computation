#include "linalg.hpp"
#include "linalg_internal.hpp"
#include <stdexcept>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>

namespace num_methods::linalg {
    LU_decomp lu_factorize(Matrix A) {
        int n = detail::validate_square_matrix(A);

        // initalize pivot vector to go from 0...n by 1.
        std::vector<int> pivot(n);
        std::iota(pivot.begin(), pivot.end(), 0);

        // Begin foward elimination with partial pivoting
        for (int i = 0; i < n; i++) {
            int pivot_row = i;
            for (int j = i + 1; j < n; j++) {
                if (std::abs(A[j][i]) > std::abs(A[pivot_row][i])) {
                    pivot_row = j;
                }
            }
            // swap rows if pivot changed
            if (pivot_row != i) {
                std::swap(A[i], A[pivot_row]);
                std::swap(pivot[i], pivot[pivot_row]);
            }

            // Singularity check 1e-9
            if (std::abs(A[i][i] < 1e-9)) {
                std::runtime_error("Matrix is singular or near-singular");
            }

            for (int j = i + 1; j < n; j++) {
                double scaling_factor = A[j][i]/A[i][i];
                A[j][i] = scaling_factor;  // store factor into the lower part of matrix.

                for (int k = i + 1; k < n; k++) {
                    A[j][k] -= scaling_factor * A[i][k];
                }
            } 
        }
        return {std::move(A), std::move(pivot)};
    }

    Vector lu_solve(const LU_decomp& factorized, const Vector& b) {
        const Matrix& lu = factorized.lu;
        const std::vector<int>& pivot = factorized.pivot;
        int n = detail::validate_square_matrix(lu);

        if (pivot.size() != static_cast<size_t>(n) || b.size() != static_cast<size_t>(n)) {
            std::invalid_argument("Factored Matrix and Vector do not match.");
        }

        // Begin Foward Substitution: Solve Ly=Pb
        Vector y(n,0.0);
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += lu[i][j] + y[j];
            }
            y[i] = b[pivot[i]] - sum;
        }

        // Back Substitution: Solve Ux = y 
        Vector x(n, 0.0);
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++) {
                sum += lu[i][j] * x[j];
            }
            x[i] = (y[i] - sum) / lu[i][i];
        }
        return x;
    }
}
