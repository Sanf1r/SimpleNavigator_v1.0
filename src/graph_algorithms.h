#ifndef GRAPH_ALGORITHMS_H_
#define GRAPH_ALGORITHMS_H_

#include <random>

class GraphAlgorithms {
 public:
  std::vector<std::vector<double>> GetLeastSpanningTree(const Graph& graph) {
    std::vector<std::vector<double>> result;
    int graph_size = graph.GetSize();
    result.resize(graph_size);
    for (int i = 0; i < graph_size; ++i) {
      result[i].resize(7, inf);
    }

    std::set<int> visited;
    std::set<int> unvisited;

    int from = 0, to = 0;

    for (int i = 0; i < graph_size; ++i) {
      unvisited.insert(i);
    }

    int random_index = Random(graph_size);

    visited.insert(random_index);
    unvisited.erase(random_index);

    while (!unvisited.empty()) {
      double min = inf;
      for (auto i = visited.begin(); i != visited.end(); ++i) {
        for (auto j = unvisited.begin(); j != unvisited.end(); ++j) {
          bool not_inf = graph(*i, *j) != inf;
          if (not_inf && graph(*i, *j) < min) {
            min = graph(*i, *j);
            from = *i;
            to = *j;
          }
        }
      }

      result[to][from] = result[from][to] = min;
      visited.insert(to);
      unvisited.erase(to);
    }
    return result;
  }

  TsmResult SolveSalesmansProblem(const Graph& graph) {
    AntsLogic al_(graph);
    return al_.SolveSalesmansProblem();
  }

 private:
  int Random(int size) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> gen(0, size - 1);
    return gen(rng);
  }
};

#endif  //  GRAPH_ALGORITHMS_H_