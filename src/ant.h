#ifndef ANT_H_
#define ANT_H_

#include "graph.h"

class Ant {
 public:
  Ant() = delete;

  explicit Ant(int start) : start_location_(start), current_location_(start) {}

  void AntMove(const Graph &graph, const AdjMatrix &pheromone_map, double a,
               double b) {
    // start run
    if (path_.vertices.empty()) {
      path_.vertices.push_back(current_location_);
      visited_.insert(current_location_);
    }

    // get neighbors
    std::vector<int> neighbor_vertexes = getNeighborVertexes(graph);

    // if nowhere to run
    if (neighbor_vertexes.empty()) {
      can_move_ = false;
      if (graph(current_location_, start_location_) != INFINITY) {
        path_.vertices.push_back(start_location_);
        path_.distance += graph(current_location_, start_location_);
      }
      return;
    }

    MakeRoulette(neighbor_vertexes, pheromone_map, graph, a, b);

    // casino
    int next_vertex = 0;
    double choose = getRandomChoice();
    int index =
        std::lower_bound(probability_.begin(), probability_.end(), choose) -
        probability_.begin();
    next_vertex = neighbor_vertexes[index];

    // add, calculate and repeat
    path_.vertices.push_back(next_vertex);
    path_.distance += graph(current_location_, next_vertex);
    visited_.insert(next_vertex);
    current_location_ = next_vertex;
  }

  void BrainwashAnt() {
    path_.distance = 0;
    path_.vertices.clear();
    visited_.clear();
    probability_.clear();
    current_location_ = start_location_;
    can_move_ = true;
  }

  bool GetMove() { return can_move_; }

  TsmResult &GetPath() { return path_; }

 private:
  TsmResult path_;

  std::set<int> visited_;
  std::vector<double> probability_;
  int start_location_ = 0, current_location_ = 0;
  bool can_move_ = true;

  double getRandomChoice() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> gen(0, 1);
    return gen(rng);
  }

  std::vector<int> getNeighborVertexes(const Graph &graph) {
    std::vector<int> vertexes;
    for (int to = 0; to < graph.GetSize(); ++to) {
      if (graph(current_location_, to) != INFINITY &&
          visited_.find(to) == visited_.end()) {
        vertexes.push_back(to);
      }
    }
    return vertexes;
  }

  void MakeRoulette(std::vector<int> &neighbor_vertexes,
                    const AdjMatrix &pheromone_map, const Graph &graph,
                    double a, double b) {
    // calculate wishes for vertexes
    probability_.clear();
    std::vector<double> wish;
    double summary_wish = 0.0f;
    for (auto &v : neighbor_vertexes) {
      double t = pheromone_map(current_location_, v);
      double n = std::pow(graph(current_location_, v), -1);
      wish.push_back(std::pow(t, a) * std::pow(n, b));
      summary_wish += wish.back();
    }

    // make roulette wheel
    int neighbor_size = neighbor_vertexes.size();
    for (int i = 0; i < neighbor_size; ++i) {
      probability_.push_back(wish[i] / summary_wish);
      if (i != 0) probability_[i] += probability_[i - 1];
    }
  }
};

#endif  //  ANT_H_