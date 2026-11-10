#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "matrix.h"

int match(const std::string &s1, const std::string &s2, int i, int j) {
    if (s1[i] == s2[j])
        return 0;
    return 1;
}

int min(std::vector<std::vector<int>> &D, const std::string &s1, const std::string &s2, int i, int j) {
    return std::min(std::min(D[i - 1][j] + 1, D[i][j - 1] + 1), D[i - 1][j - 1] + match(s1, s2, i, j));
}


int main() {
    std::string s1 = "GIBLARTAR";
    std::string s2 = "LABRADOR";

    Matrix D(s1, s2);
    D.print();
}
