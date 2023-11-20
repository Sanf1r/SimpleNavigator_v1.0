#ifndef ANT_H_
#define ANT_H_

#include <random>
#include <set>

#include "graph.h"

class Ant {
 public:
  Ant() = delete;

  explicit Ant(int start) : start_location_(start), current_location_(start) {}

  void AntMove(const Graph &graph, const AdjMatrix &pheromone_map, double a,
               double b);

  void BrainwashAnt();

  bool GetMove();

  TsmResult &GetPath();

 private:
  TsmResult path_;

  std::set<int> visited_;
  std::vector<double> probability_;
  int start_location_ = 0, current_location_ = 0;
  bool can_move_ = true;

  double getRandomChoice();

  std::vector<int> getNeighborVertexes(const Graph &graph);

  void MakeRoulette(std::vector<int> &neighbor_vertexes,
                    const AdjMatrix &pheromone_map, const Graph &graph,
                    double a, double b);
};

#endif  //  ANT_H_