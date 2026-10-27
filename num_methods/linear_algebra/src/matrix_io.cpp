#include "linalg.hpp"
#include <cstddef>
#include <iostream>
#include <iomanip>

namespace num_methods::linalg {
    void print_matrix(const Matrix& matrix, const std::string& label) {
        if (!label.empty()) {
            std::cout << "\n---" << label << " ---" << std::endl;
        }
        if (matrix.empty() || matrix[0].empty()) {
            std::cout << " [Empty Matrix]" << std::endl;
            return;
        }
        std::cout << std::fixed << std::setprecision(4);

        for (const auto& row:matrix) {
            std::cout << "  [";
            for (size_t c = 0; c < row.size(); ++c) {
                std::cout << std::setw(9) << row[c];
                if (c < row.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << " ]" << std::endl;
        }
        std::cout << std::endl;
    }
}
