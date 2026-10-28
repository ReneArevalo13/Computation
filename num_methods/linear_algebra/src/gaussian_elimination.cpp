// Gaussian Elimination, with partial pivoting,routine to solve system of equations Ax=b
// Helper functions split into forward substitution and backwards substitution
// Helper functions in an anonomyous namespace to not be client facing
// Client only interacfaces with main gaussian_elimintation() method.
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
}
