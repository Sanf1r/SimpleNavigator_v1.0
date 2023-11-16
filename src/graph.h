#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
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

  const std::vector<double>& GetData() const { return data_.GetData(); }

  bool LoadGraph(const std::string& path) {
    std::ifstream inFile(path);
    std::string temp;
    std::getline(inFile, temp);
    std::istringstream ss(temp);
    int c = 0;

    ss >> size_;
    if (size_ < 1) return false;

    data_.Init(size_);

    for (int i = 0; i < size_; ++i) {
      std::getline(inFile, temp);
      std::istringstream ss(temp);

      int x;
      c = 0;
      while (ss >> x || !ss.eof()) {
        if (ss.fail()) return false;
        if (x != 0) {
          data_.Push(x);
        } else {
          data_.Push(inf);
        }
        c++;
      }
      if (c != size_) return false;
    }
    return true;
  }

 private:
  int size_ = 0;
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

#endif  //  GRAPH_H_