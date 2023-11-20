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
  TsmResult SolveTravelingSalesmanProblem();

  std::vector<std::vector<double>> GetLeastSpanningTree();

  std::vector<int> BreadthFirstSearch(int num);

  std::vector<int> DepthFirstSearch(int num);

  long GetShortestPathBetweenVertices(int vertex1, int vertex2);

  AdjMatrix GetShortestPathsBetweenAllVertices();

  bool LoadGraphFromFile(const std::string& path);

  bool ExportGraphToDot(const std::string& path);

  bool UndirectedCheck();

  int GetSize();

 private:
  Graph graph_;
  GraphAlgorithms ga_;
};

#endif  //  MODEL_H_
