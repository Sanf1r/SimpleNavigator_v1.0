#ifndef MODEL_H_
#define MODEL_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <vector>

#include "adj_matrix.h"
#include "ant.h"
#include "ants_logic.h"
#include "graph_algorithms.h"

class Model {
 public:
  TsmResult SolveTravelingSalesmanProblem() {
    return ga_.SolveSalesmansProblem(graph_);
  }

  std::vector<std::vector<double>> GetLeastSpanningTree() {
    return ga_.GetLeastSpanningTree(graph_);
  }

  std::vector<int> BreadthFirstSearch(int num) {
    return ga_.BreadthFirstSearch(graph_, num);
  }

  std::vector<int> DepthFirstSearch(int num) {
    return ga_.DepthFirstSearch(graph_, num);
  }

  long GetShortestPathBetweenVertices(int vertex1, int vertex2) {
    return ga_.GetShortestPathBetweenVertices(graph_, vertex1, vertex2);
  }

  AdjMatrix GetShortestPathsBetweenAllVertices() {
    return ga_.GetShortestPathsBetweenAllVertices(graph_);
  }

  bool LoadGraph(const std::string& path) { return graph_.LoadGraph(path); }

  bool UndirectedCheck() { return ga_.UndirectedCheck(graph_); }

  int GetSize() { return graph_.GetSize(); }

 private:
  Graph graph_;
  GraphAlgorithms ga_;
};

#endif  //  MODEL_H_
