#ifndef ANALYSIS_OF_ALGORITHMS_MATRIX_H
#define ANALYSIS_OF_ALGORITHMS_MATRIX_H

#include <vector>
#include <iostream>

class Matrix {
    std::vector<std::vector<int>> data;
    size_t rows;
    size_t cols;
public:
    Matrix(const std::string &s1, const std::string &s2);

    int &at(size_t i, size_t j);

    [[nodiscard]]
    const int &at(size_t i, size_t j) const;

    [[nodiscard]]
    size_t getRows() const;

    [[nodiscard]]
    size_t getCols() const;

    void print() const;
};


#endif //ANALYSIS_OF_ALGORITHMS_MATRIX_H
