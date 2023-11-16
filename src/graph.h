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
    data_.Clear();

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

#endif  //  GRAPH_H_