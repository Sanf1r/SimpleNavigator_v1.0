#include <iostream>
#include <random>
#include <set>
#include <vector>

const double inf = 1.0 / 0.0;

class Graph {
 public:
  Graph() {
    data_.resize(size_);

    data_[0] = {inf, 7, inf, 5, inf, inf, inf};
    data_[1] = {7, inf, 8, 9, 7, inf, inf};
    data_[2] = {inf, 8, inf, inf, 5, inf, inf};
    data_[3] = {5, 9, inf, inf, 15, 6, inf};
    data_[4] = {inf, 7, 5, 15, inf, 8, 9};
    data_[5] = {inf, inf, inf, 6, 8, inf, 11};
    data_[6] = {inf, inf, inf, inf, 9, 11, inf};
  }

  double& operator()(int row, int columns) { return data_[row][columns]; }

  int GetSize() { return size_; }

 private:
  int size_ = 7;
  std::vector<std::vector<double>> data_;
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

int main() {
  Graph one;
  std::vector<std::vector<double>> res = GetLeastSpanningTree(one);

  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 7; ++j) {
      std::cout << res[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // hi

  return 0;
}