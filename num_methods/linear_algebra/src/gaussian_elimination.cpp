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

namespace num_methods::linalg {
    namespace {
        void forward_elimination(Matrix& A, Vector& b) {

        }
        Vector backward_substitution(const Matrix& A, const Vector& b) {

        }
    }
    // Note that in the client facing function call here we are passing by value.
    // This way we create a copy that can be worked on locally by the above helper functions.
    Vector gaussian_elimination(Matrix A, Vector b) {
        int n = A.size();
        // safety check of vector and matrix sizes.
        // Cast n to a size_t for proper comparison
        if (n==0 || b.size() != static_cast<size_t>(n)) {
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

