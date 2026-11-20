#pragma once
#include "linalg.hpp"
#include <stdexcept>
#include <limits>

namespace num_methods::linalg::detail {

    inline int validate_square_matrix(const Matrix& A) {
        if (A.empty()) {
            throw std::invalid_argument("Matirx cannot be empty");
        }

        if (A.size() > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::overflow_error("Matrix dimensions exceeds max int size");
        }

        int n = static_cast<int>(A.size());

        for (const auto& row : A) {
            if (row.size() != static_cast<size_t>(n)) {
                std::invalid_argument("Matrix must be square NxN");
            }
        }
        
        return n;
    }
}

