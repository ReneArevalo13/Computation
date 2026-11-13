#include <catch2/catch_all.hpp>
#include "linalg.hpp"
#include <stdexcept>

using namespace num_methods::linalg;
using Catch::Matchers::WithinAbs;

// Margin of error allowance for floating-point comparisons
const double EPSILON = 1e-9;

TEST_CASE("Gaussian Elimination - Standard 4x4 System", "[linalg][solvers]") {
    Matrix A = {
        { 2.0,  1.0, -1.0,  2.0 },
        { 4.0,  5.0, -3.0,  6.0 },
        {-2.0,  5.0, -2.0,  6.0 },
        { 4.0, 11.0, -4.0,  8.0 }
    };
    Vector b = { 5.0, 9.0, 4.0, 2.0 };

    Vector x = gaussian_elimination(A, b);

    REQUIRE(x.size() == 4);
    REQUIRE_THAT(x[0], WithinAbs(1.0, EPSILON));
    REQUIRE_THAT(x[1], WithinAbs(-2.0, EPSILON));
    REQUIRE_THAT(x[2], WithinAbs(1.0, EPSILON));
    REQUIRE_THAT(x[3], WithinAbs(3.0, EPSILON));
}

TEST_CASE("Gaussian Elimination - Requires Row Pivoting", "[linalg][pivoting]") {
    // Row 0 has a 0.0 on the diagonal. Must pivot with Row 1!
    Matrix A = {
        { 0.0,  2.0,  1.0 },
        { 1.0, -2.0, -3.0 },
        {-1.0,  1.0,  2.0 }
    };
    Vector b = { 4.0, 0.0, 1.0 };

    Vector x = gaussian_elimination(A, b);

    REQUIRE(x.size() == 3);
    REQUIRE_THAT(x[0], WithinAbs(-8.0, EPSILON));
    REQUIRE_THAT(x[1], WithinAbs(5.0, EPSILON));
    REQUIRE_THAT(x[2], WithinAbs(-6.0, EPSILON));
}

TEST_CASE("Identity Check", "[linalg][identity]") {
    // Row 0 has a 0.0 on the diagonal. Must pivot with Row 1!
    Matrix A = {
        { 1.0,  0.0,  0.0 },
        { 0.0,  1.0,  0.0 },
        { 0.0,  0.0,  1.0 }
    };
    Vector b = { 4.0, 5.0, 7.0 };

    Vector x = gaussian_elimination(A, b);

    REQUIRE(x.size() == 3);
    REQUIRE_THAT(x[0], WithinAbs(4.0, EPSILON));
    REQUIRE_THAT(x[1], WithinAbs(5.0, EPSILON));
    REQUIRE_THAT(x[2], WithinAbs(7.0, EPSILON));
}

TEST_CASE("Gaussian Elimination - Minimal System", "[linalg][minimal]") {
    // Row 0 has a 0.0 on the diagonal. Must pivot with Row 1!
    Matrix A = {
        { 5.0 },
    };
    Vector b = { 10.0 };

    Vector x = gaussian_elimination(A, b);

    REQUIRE(x.size() == 1);
    REQUIRE_THAT(x[0], WithinAbs(2.0, EPSILON));
}

TEST_CASE("Gaussian Elimination - Guardrails and Error Handling", "[linalg][errors]") {
    
    SECTION("Non-square matrix exception") {
        Matrix non_square = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0} // Missing third row
        };
        Vector b = {1.0, 2.0};
        
        REQUIRE_THROWS_AS(gaussian_elimination(non_square, b), std::invalid_argument);
    }

    SECTION("Mismatched vector size exception") {
        Matrix A = {
            {1.0, 0.0},
            {0.0, 1.0}
        };
        Vector b = {1.0, 2.0, 3.0}; // Dimension mismatch
        
        REQUIRE_THROWS_AS(gaussian_elimination(A, b), std::invalid_argument);
    }

    SECTION("Singular matrix exception") {
        Matrix singular = {
            {1.0, 2.0},
            {2.0, 4.0} // Row 2 is exactly a multiple of Row 1 (No unique solution)
        };
        Vector b = {5.0, 10.0};
        
        REQUIRE_THROWS_AS(gaussian_elimination(singular, b), std::runtime_error);
    }

    SECTION("Near-singular matrix, triggers precision threshold") {
        Matrix near_singular = {
            {1.0, 2.0},
            {2.0, 4.0 + 1e-12} // Row 2 is exactly a multiple of Row 1 (No unique solution)
        };
        Vector b = {5.0, 10.0};
        
        REQUIRE_THROWS_AS(gaussian_elimination(near_singular, b), std::runtime_error);
    }
}

