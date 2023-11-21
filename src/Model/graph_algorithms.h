#ifndef A2_SIMPLENAVIGATOR_SRC_MODEL_GRAPH_ALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_SRC_MODEL_GRAPH_ALGORITHMS_H_

#include <algorithm>
#include <random>
#include <set>

#include "ant.h"
#include "ants_logic.h"
#include "graph.h"
#include "s21_queue.h"
#include "s21_stack.h"

namespace s21 {

class GraphAlgorithms {
 public:
  std::vector<int> BreadthFirstSearch(const Graph& graph, int start_vertex);

  std::vector<int> DepthFirstSearch(const Graph& graph, int start_vertex);

  long GetShortestPathBetweenVertices(const Graph& graph, int vertex1,
                                      int vertex2);

  AdjMatrix GetShortestPathsBetweenAllVertices(const Graph& graph);

  std::vector<std::vector<double>> GetLeastSpanningTree(const Graph& graph);

  TsmResult SolveSalesmansProblem(const Graph& graph);

  bool UndirectedCheck(const Graph& graph);

 private:
  int Random(int size);
};

}  // namespace s21

#endif  //  A2_SIMPLENAVIGATOR_SRC_MODEL_GRAPH_ALGORITHMS_H_
