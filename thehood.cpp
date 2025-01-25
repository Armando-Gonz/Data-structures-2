#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

template <typename T>
class TheHood {
 private:
  int vertex_counter;
  std::vector<std::vector<T>> adjacency_list;
  std::vector<std::vector<T>> reversed_adjacency_list;

 public:
  TheHood(int n)
      : vertex_counter(n), adjacency_list(n), reversed_adjacency_list(n) {}

  void addEdge(T start, T end) {
    adjacency_list[start].push_back(end);
    reversed_adjacency_list[end].push_back(start);
  }

  void depthFirstSearch(T node, std::vector<bool> &visited,
                        std::stack<T> &finish_stack) {
    visited[node] = true;
    for (auto &neighbor : adjacency_list[node]) {
      if (!visited[neighbor]) {
        depthFirstSearch(neighbor, visited, finish_stack);
      }
    }
    finish_stack.push(node);
  }

  void reverseDepthFirstSearch(T node, std::vector<bool> &visited,
                               std::vector<T> &component) {
    visited[node] = true;
    component.push_back(node);
    for (auto &neighbor : reversed_adjacency_list[node]) {
      if (!visited[neighbor]) {
        reverseDepthFirstSearch(neighbor, visited, component);
      }
    }
  }

  std::vector<std::vector<T>>
  findStronglyConnectedComponents() {  // reduced to SCCS in the rest of the
                                       // code
    std::stack<T> finish_stack;
    std::vector<bool> visited(vertex_counter, false);

    for (T i = 0; i < vertex_counter; ++i) {
      if (!visited[i]) {
        depthFirstSearch(i, visited, finish_stack);
      }
    }

    visited.assign(vertex_counter, false);
    std::vector<std::vector<T>> sccs;

    while (!finish_stack.empty()) {
      T node = finish_stack.top();
      finish_stack.pop();

      if (!visited[node]) {
        std::vector<T> component;
        reverseDepthFirstSearch(node, visited, component);
        sccs.push_back(component);
      }
    }

    return sccs;
  }

  TheHood<T> compressGraph(const std::vector<std::vector<T>> &sccs) {
    int new_vertex_count = sccs.size();
    TheHood<T> compressed_graph(new_vertex_count);

    for (int i = 0; i < sccs.size(); ++i) {
      for (auto &node : sccs[i]) {
        for (auto &neighbor : adjacency_list[node]) {
          int node_scc = findSCCIndex(sccs, node);
          int neighbor_scc = findSCCIndex(sccs, neighbor);
          if (node_scc != neighbor_scc) {
            compressed_graph.addEdge(node_scc, neighbor_scc);
          }
        }
      }
    }

    return compressed_graph;
  }

  int findSCCIndex(const std::vector<std::vector<T>> &sccs, T vertex) {
    for (int i = 0; i < sccs.size(); ++i) {
      if (std::find(sccs[i].begin(), sccs[i].end(), vertex) != sccs[i].end()) {
        return i;
      }
    }
    return -1;
  }

  std::pair<int, int> calculateDegrees() {
    std::vector<int> in_degree(vertex_counter, 0);
    std::vector<int> out_degree(vertex_counter, 0);

    for (int i = 0; i < vertex_counter; ++i) {
      for (auto &neighbor : adjacency_list[i]) {
        ++out_degree[i];
        ++in_degree[neighbor];
      }
    }

    int zero_in_vertex = 0, zero_out_vertex = 0;
    for (int i = 0; i < in_degree.size(); ++i) {
      if (in_degree[i] == 0) {
        ++zero_in_vertex;
      }
    }

    for (int i = 0; i < out_degree.size(); ++i) {
      if (out_degree[i] == 0) {
        ++zero_out_vertex;
      }
    }

    return {zero_in_vertex, zero_out_vertex};
  }
};

template <typename T>
void solveTheHood(int n, int m) {
  TheHood<T> thehood(n);

  T u, v;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    thehood.addEdge(u - 1, v - 1);
  }

  auto sccs = thehood.findStronglyConnectedComponents();

  if (sccs.size() == 1) {
    std::cout << 0 << std::endl;
    return;
  }

  TheHood<T> compressed_thehood = thehood.compressGraph(sccs);

  auto degrees = compressed_thehood.calculateDegrees();
  std::cout << std::max(degrees.first, degrees.second) << std::endl;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  solveTheHood<int>(n, m);

  return 0;
}
