#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

int det(const std::vector<std::vector<int>>& M) {
    int n = M.size();
    if (n == 1) return M[0][0];
    if (n == 2) return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    int total = 0;
    for (int c = 0; c < n; ++c) {
        std::vector<std::vector<int>> sub(n - 1, std::vector<int>(n - 1));
        for (int i = 1; i < n; ++i) {
            int k = 0;
            for (int j = 0; j < n; ++j) {
                if (j != c) sub[i - 1][k++] = M[i][j];
            }
        }
        int sign = (c % 2 == 0) ? 1 : -1;
        total += sign * M[0][c] * det(sub);
    }
    return total;
}

int main() {
    // Матриця для тестування
    std::vector<std::vector<int>> matrix = {
        {3, 1, 3, 5, 8},
        {1, 8, 6, 6, 7},
        {1, 7, 6, 6, 1},
        {3, 8, 8, 2, 8},
        {6, 9, 7, 9, 3}
    };

    std::cout << "=== C++ Implementation ===" << std::endl;
    std::cout << "Matrix (5x5):" << std::endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    
    int determinant = 0;
    for (int i = 0; i < 10000; ++i) {
        determinant = det(matrix);
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "\nDeterminant: " << determinant << std::endl;
    std::cout << "Time for 10000 computations: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "Average time per computation: " << (elapsed.count() / 10000.0) * 1000000 << " microseconds" << std::endl;

    return 0;
}
