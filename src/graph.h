#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <random>
#include <set>
#include <vector>

const double inf = 1.0 / 0.0;

class Graph {
 public:
  Graph() = default;

  int GetSize() const { return size_; }

  const double& operator()(int row, int columns) const {
    return data_(row, columns);
  }

  double& operator()(int row, int columns) { return data_(row, columns); }

  const std::vector<std::vector<double>>& GetData() const {
    return data_.GetData();
  }

 private:
  int size_ = 11;
  AdjMatrix data_;
};

struct TsmResult {
  std::vector<int> vertices;
  double distance = 0;
};

int Random(int size) {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> gen(0, size - 1);
  return gen(rng);
}

std::vector<std::vector<double>> GetLeastSpanningTree(Graph& graph) {
  std::vector<std::vector<double>> result;
  result.resize(7);
  for (int i = 0; i < 7; ++i) {
    result[i].resize(7, inf);
  }

  std::set<int> visited;
  std::set<int> unvisited;

  int graph_size = graph.GetSize();
  int from, to;

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

#endif  //  GRAPH_H_