#include <iostream>
#include <queue>
#include <vector>

class Milk {
 public:
  std::vector<std::vector<int>> adj;

  Milk(
      int n) {  // with this we can initialize the list of empty vectors vectors
    adj.resize(n);
  }

  void add_edge(int start, int to) {
    adj[start].push_back(to);
    adj[to].push_back(start);
  }

  void BFS(int start, int nodes, std::vector<int>& distance) {
    distance.assign(nodes, -1);
    distance[start] = 0;
    std::queue<int> q;
    q.push(start);
    while (!q.empty()) {
      int node = q.front();
      q.pop();

      for (int i = 0; i < adj[node].size(); ++i) {
        int neighbor = adj[node][i];
        if (distance[neighbor] == -1) {
          distance[neighbor] = distance[node] + 1;
          q.push(neighbor);
        }
      }
    }
  }

  int find_shortest_distance(int nodes, std::vector<int>& first,
                             std::vector<int>& second,
                             std::vector<int>& third) {
    int min_sum = nodes * 2;
    for (int i = 0; i < nodes; i++) {
      int current_sum = first[i] + second[i] + third[i];
      if (current_sum < min_sum) {
        min_sum = current_sum;
      }
    }
    return min_sum;
  }
};

int main() {
  int n, m, s1, s2, s3;
  std::cin >> n >> m >> s1 >> s2 >> s3;

  Milk graph(n);

  for (int i = 0; i < m; i++) {
    int start, to;
    std::cin >> start >> to;
    graph.add_edge(start - 1, to - 1);
  }

  std::vector<int> distance1(n), distance2(n), distance3(n);

  graph.BFS(s1 - 1, n, distance1);
  graph.BFS(s2 - 1, n, distance2);
  graph.BFS(s3 - 1, n, distance3);

  int result = graph.find_shortest_distance(n, distance1, distance2, distance3);

  std::cout << result << std::endl;

  return 0;
}
