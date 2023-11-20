#ifndef GRAPH_H_
#define GRAPH_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

#include "adj_matrix.h"

class Graph {
 public:
  Graph() = default;

  int GetSize() const { return size_; }

  const double& operator()(int row, int columns) const {
    return data_(row, columns);
  }

  double& operator()(int row, int columns) { return data_(row, columns); }

  const std::vector<double>& GetData() const { return data_.GetData(); }

  bool LoadGraphFromFile(const std::string& path);

  bool ExportGraphToDot(const std::string& path);

 private:
  int size_ = 0;
  AdjMatrix data_;
};

struct TsmResult {
  std::vector<int> vertices;
  double distance = 0;
};

#endif  //  GRAPH_H_