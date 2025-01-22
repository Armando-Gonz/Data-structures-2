#include <cstdint>
#include <iostream>

class Fibonacci {
 public:
  const uint64_t mod = 1000003;

  void matrix_multiplication(uint64_t A[2][2], uint64_t B[2][2]) {
    uint64_t C[2][2];
    C[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % mod;
    C[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % mod;
    C[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % mod;
    C[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % mod;

    A[0][0] = C[0][0];
    A[0][1] = C[0][1];
    A[1][0] = C[1][0];
    A[1][1] = C[1][1];
  }

  void powerMatrix(uint64_t matrix[2][2], uint64_t power) {
    uint64_t identity[2][2] = {{1, 0}, {0, 1}};
    while (power) {
      if (power % 2) {
        matrix_multiplication(identity, matrix);
      }
      matrix_multiplication(matrix, matrix);
      power /= 2;
    }
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        matrix[i][j] = identity[i][j];
      }
    }
  }

  uint64_t answer(uint64_t n) {
    uint64_t M[2][2] = {{1, 1}, {1, 0}};
    if (n == 0) {
      return 0;
    } else if (n == 1) {
      return 1;
    }
    powerMatrix(M, n - 1);
    return M[0][0];
  }
};

int main() {
  uint64_t n;
  std::cin >> n;
  Fibonacci f;
  std::cout << f.answer(n - 1) << std::endl;
  return 0;
}
