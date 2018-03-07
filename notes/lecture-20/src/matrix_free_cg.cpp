// Filename: matrix_free_cg.cpp (part of MTL4)

#include <iostream>
#include <boost/numeric/mtl/mtl.hpp>
#include <boost/numeric/itl/itl.hpp>


int main(int, char**)
{
    // For a more realistic example set size to 1000 or larger
    const int size = 10, N = size * size;

    // Define matrix type
    typedef mtl::mat::poisson2D_dirichlet  matrix_type;

    // Instantiate matrix
    matrix_type A(size, size);

    // Set preconditioner
    itl::pc::identity<matrix_type> P(A);

    // Define solution and righ-hand-side vector
    mtl::dense_vector<double> x(N, 1.0), b(N);

    // Cook-up the problem to solve
    b = A * x;

    // Set initial guess
    x= 0;

    // Define iteration (exit r < b*1e-11 or 100 iterations)
    itl::cyclic_iteration<double> iter(b, 100, 1.e-11, 0.0, 5);

    // Solve the Ax == b problem using conjugate gradient method
    cg(A, x, b, P, iter);

    return 0;
}

