#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

struct cockroach {
  int max_size = 0;
  std::set<int> max_clique;

  void printcockraoches() {
    std::vector<int> clique_vector(max_clique.begin(), max_clique.end());
    for (int i = 0; i < clique_vector.size(); i++) {
      std::cout << clique_vector[i] << " ";
    }
    std::cout << std::endl;
  }

  void BronKerbosch(std::vector<std::vector<int>> &graph, std::vector<int> &r,
                    std::vector<int> &p, std::vector<int> &x) {
    if (p.empty() && x.empty()) {
      if (r.size() > max_size) {
        max_size = r.size();
        max_clique.clear();
        for (int v : r) max_clique.insert(v);
      }
      return;
    }
    int pivot = p.empty() ? x.front() : p.front();
    std::vector<int> p_copy = p;
    for (int i = 0; i < p_copy.size(); ++i) {
      int v = p_copy[i];
      if (graph[pivot][v] == 1) {
        continue;
      }

      r.push_back(v);

      std::vector<int> new_p, new_x;
      for (int i = 0; i < p.size(); i++) {
        int neighbor = p[i];
        if (graph[v][neighbor] == 1) {
          new_p.push_back(neighbor);
        }
      }
      for (int i = 0; i < x.size(); i++) {
        int neighbor = x[i];
        if (graph[v][neighbor] == 1) {
          new_x.push_back(neighbor);
        }
      }

      BronKerbosch(graph, r, new_p, new_x);

      p.erase(std::remove(p.begin(), p.end(), v), p.end());
      x.push_back(v);

      r.pop_back();
    }
  }
};

int main() {
  uint64_t n;
  std::cin >> n;

  std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> matrix[i][j];
    }
  }

  std::vector<int> r, p, x;
  for (int i = 0; i < n; i++) {
    p.push_back(i);
  }

  cockroach c;
  c.BronKerbosch(matrix, r, p, x);
  c.printcockraoches();

  return 0;
}
