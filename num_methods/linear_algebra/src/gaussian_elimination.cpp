// Gaussian Elimination, with partial pivoting,routine to solve system of equations Ax=b
// Helper functions split into forward substitution and backwards substitution
// Helper functions in an anonomyous namespace to not be client facing
// Client only interacfaces with main gaussian_elimintation() function.
// Matrices are stored as nested vectors: vector<vector<double>>
// Will try a flat structure later to see if how much faster that will be 
//

#include <linalg.hpp>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <utility>

namespace num_methods::linalg {
    namespace {
        void forward_elimination(Matrix& A, Vector& b) {
            // Turns A into an upper-triangular matrix adjusts b as needed
            int n = A.size();
            for (int i = 0; i < n; i++) {
                // Implement partial pivoting
                int pivot_row = i;
                for (int j = i + 1; j < n; j++) {
                    if (std::abs(A[j][i]) > std::abs(A[pivot_row][i])) {
                        pivot_row = j;
                    }
                }
                // Swap rows if a better pivot was found
                if (pivot_row != i) {
                    std::swap(A[i], A[pivot_row]);
                    std::swap(b[i], b[pivot_row]);
                }

                // Numerical safety check: detect singular Matrices
                if (std::abs(A[i][i]) < 1e-9) {
                    throw std::runtime_error("Matrix Singular or near singular");
                }

                // Elimination steps
                // Save on flops and do not scale pivot to 1 (Doolitle)
                for (int j = i + 1; j < n; j++) {
                    double scaling_factor = A[j][i]/A[i][i];
                    for (int k = i; k < n; k++) {
                        A[j][k] -= scaling_factor * A[i][k];
                    }
                    b[j] -= scaling_factor * b[i];
                }
            }
        }
        Vector backward_substitution(const Matrix& A, const Vector& b) {
            // solves upper-triangular system Ax=b. Returns the solution vector x.
            int n = A.size();
            Vector x(n,0.0);        // Vector is vector<double>
            for (int i = n - 1; i >= 0; i--) {
                double sum = 0.0;
                for (int j = i + 1; j < n; j++) {
                    sum += A[i][j] * x[j];
                }
                x[i] = (b[i] - sum) / A[i][i];
            }
            return x;

        }
    }
    // Note that in the client facing function call here we are passing by value.
    // This way we create a copy that can be worked on locally by the above helper functions.
    Vector gaussian_elimination(Matrix A, Vector b) {
        int n = A.size();
        // safety check of vector and matrix sizes.
        // Cast n to a size_t for proper comparison
        if (n==0 || b.size() != static_cast<size_t>(n) || b.size() != static_cast<size_t>(A[0].size())) {
            throw std::invalid_argument("Matrix dimensions do not match vector dimensions");
        }
        // Solving Routine: forward_elimination -> backward_substitution
        // returning the solution vector from backward_substitution function.
        // Instead of copying the numbers, the compiler performs a pointer handoff:
        // it simply transfers ownership of the memory address containing your solution 
        // vector directly to the variable in main.cpp. It runs in O(1) constant time.
        forward_elimination(A,b);
        return backward_substitution(A,b);
    }
}
