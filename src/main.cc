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

// std::vector<int> GetLeastSpanningTree(Graph& graph) {}

int main() {
  std::vector<std::pair<int, int>> path;
  Graph one;
  std::set<int> visited;
  std::set<int> unvisited;
  int graph_size = one.GetSize();
  int from, to;

  for (int i = 0; i < graph_size; ++i) {
    unvisited.insert(i);
  }

  //   int random_index = Random(graph_size);

  visited.insert(3);
  unvisited.erase(3);
  int c = 1;
  while (!unvisited.empty()) {
    double min = inf;
    for (auto i = visited.begin(); i != visited.end(); ++i) {
      for (auto j = unvisited.begin(); j != unvisited.end(); ++j) {
        bool not_inf = one(*i, *j) != inf;
        if (not_inf && one(*i, *j) < min) {
          min = one(*i, *j);
          from = *i;
          to = *j;
        }
      }
    }
    path.push_back(std::pair(from, to));
    visited.insert(to);
    unvisited.erase(to);

    std::cout << "loop number = " << c++ << std::endl;
  }

  std::vector<char> letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

  for (auto data : path) {
    std::cout << letters[data.first] << " " << letters[data.second]
              << std::endl;
  }

  return 0;
}