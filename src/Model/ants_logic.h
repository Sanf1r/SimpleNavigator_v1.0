#ifndef A2_SIMPLENAVIGATOR_SRC_MODEL_ANTS_LOGIC_H_
#define A2_SIMPLENAVIGATOR_SRC_MODEL_ANTS_LOGIC_H_

#include "ant.h"
#include "graph.h"

namespace s21 {

class AntsLogic {
 public:
  AntsLogic() = delete;
  explicit AntsLogic(const Graph &graph);

  TsmResult SolveSalesmansProblem();

 private:
  Graph graph_;
  AdjMatrix pheromone_;
  std::vector<Ant> ants_;

  int graph_size_ = 0;
  const int kMaxLoopsWithNoGains_ = 5000;
  const double kAlpha_ = 4.0;
  const double kBeta_ = 1.0;
  const double kQ_ = 1.0;
  const double kEvap_ = 0.8;

  void CreateAnts();

  void BrainwashAnts();

  void UpdateGlobalPheromone(const AdjMatrix &lpu);
};
}  // namespace s21

#endif  //  A2_SIMPLENAVIGATOR_SRC_MODEL_ANTS_LOGIC_H_