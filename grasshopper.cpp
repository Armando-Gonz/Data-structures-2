#include <cstdint>
#include <iostream>
#include <vector>
class Grasshopper {
 public:
  const uint64_t mod = 1000003;

  void matrix_multiplication(
      std::vector<std::vector<uint64_t>> *matrix_1,
      const std::vector<std::vector<uint64_t>> *matrix_2) {
    std::vector<std::vector<uint64_t>> result_matrix(
        5, std::vector<uint64_t>(5, 0));

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        uint64_t sum = 0;
        for (int k = 0; k < 5; k++) {
          sum = (sum + ((*matrix_1)[i][k] * (*matrix_2)[k][j]) % mod) % mod;
        }
        result_matrix[i][j] = sum;
      }
    }

    *matrix_1 = result_matrix;
  }

  void power_matrix(std::vector<std::vector<uint64_t>> &matrix, uint64_t n) {
    if (n <= 1) {
      return;
    }

    std::vector<std::vector<uint64_t>> identity = {{1, 1, 1, 1, 1},
                                                   {1, 0, 0, 0, 0},
                                                   {0, 1, 0, 0, 0},
                                                   {0, 0, 1, 0, 0},
                                                   {0, 0, 0, 1, 0}};
    power_matrix(matrix, n / 2);
    matrix_multiplication(&matrix, &matrix);

    if (n % 2 != 0) {
      matrix_multiplication(&matrix, &identity);
    }
  }

  uint64_t second_multiplication(
      const std::vector<std::vector<uint64_t>> &matrix,
      const std::vector<uint64_t> &vector) {
    uint64_t result = 0;

    for (int i = 0; i < 5; i++) {
      uint64_t sum = 0;
      for (int j = 0; j < 5; j++) {
        sum = (sum + (matrix[i][j] * vector[j]) % mod) % mod;
      }
      if (i == 0) result = sum;
    }

    return result;
  }

  uint64_t steps(uint64_t n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;
    if (n == 3) return 2;
    if (n == 4) return 4;
    if (n == 5) return 8;

    std::vector<std::vector<uint64_t>> base_matrix = {{1, 1, 1, 1, 1},
                                                      {1, 0, 0, 0, 0},
                                                      {0, 1, 0, 0, 0},
                                                      {0, 0, 1, 0, 0},
                                                      {0, 0, 0, 1, 0}};

    power_matrix(base_matrix, n - 5);
    std::vector<uint64_t> initial_values = {8, 4, 2, 1, 1};

    return second_multiplication(base_matrix, initial_values);
  }
};

int main() {
  uint64_t n;
  std::cin >> n;
  Grasshopper g;
  std::cout << g.steps(n) << std::endl;
  return 0;
}
