#include "matrix.h"


Matrix::Matrix(const std::string &s1, const std::string &s2) {
    rows = s1.size();
    cols = s2.size();
    data.resize(rows + 1, std::vector<int>(cols + 1, 0));
}

int &Matrix::at(size_t i, size_t j) {
    return data[i + 1][j + 1];
}

[[nodiscard]]
const int &Matrix::at(size_t i, size_t j) const {
    return data[i + 1][j + 1];
}

[[nodiscard]]
size_t Matrix::getRows() const {
    return rows;
}

[[nodiscard]]
size_t Matrix::getCols() const {
    return cols;
}

void Matrix::print() const {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
