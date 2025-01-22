#include <cstdint>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <utility>
#include <vector>

class Planet {
 public:
  Planet(uint64_t number_of_Nodes);
  void BuildGraph(uint64_t cost1, uint64_t cost2);
  uint64_t ShortestPath(uint64_t start, uint64_t end);

 private:
  uint64_t Count;
  std::vector<std::list<std::pair<uint64_t, uint64_t>>> adjacencyList;
};

Planet::Planet(uint64_t number_of_nodes) : Count(number_of_nodes) {
  adjacencyList.resize(Count);
}

void Planet::BuildGraph(uint64_t cost1, uint64_t cost2) {
  for (uint64_t i = 0; i < Count; i++) {
    uint64_t nextNode1 = (i + 1) % Count;
    uint64_t nextNode2 = ((i * i) + 1) % Count;
    adjacencyList[i].emplace_back(nextNode1, cost1);
    adjacencyList[i].emplace_back(nextNode2, cost2);
  }
}

uint64_t Planet::ShortestPath(uint64_t start, uint64_t end) {
  std::vector<uint64_t> distances(Count, std::numeric_limits<uint64_t>::max());
  distances[start] = 0;

  using Pair = std::pair<uint64_t, uint64_t>;
  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> minHeap;
  minHeap.push({0, start});

  while (!minHeap.empty()) {
    uint64_t current = minHeap.top().second;
    minHeap.pop();

    for (auto it = adjacencyList[current].begin();
         it != adjacencyList[current].end(); ++it) {
      uint64_t next = it->first;
      uint64_t edgeWeight = it->second;

      if (distances[current] != std::numeric_limits<uint64_t>::max() &&
          distances[current] + edgeWeight < distances[next]) {
        distances[next] = distances[current] + edgeWeight;
        minHeap.push({distances[next], next});
      }

      if (current == end) {
        return distances[current];
      }
    }
  }

  return distances[end];
}

int main() {
  uint64_t cost1, cost2, totalNodes, start, end;

  std::cin >> cost1 >> cost2 >> totalNodes >> start >> end;

  Planet planet(totalNodes);

  planet.BuildGraph(cost1, cost2);

  uint64_t result = planet.ShortestPath(start, end);

  std::cout << result << std::endl;

  return 0;
}
