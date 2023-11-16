#ifndef MODEL_H_
#define MODEL_H_

#include "adj_matrix.h"
#include "graph.h"
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

  void LoadGraph(const std::string& path) { graph_.LoadGraph(path); }

 private:
  Graph graph_;
  GraphAlgorithms ga_;
};

#endif  //  MODEL_H_
