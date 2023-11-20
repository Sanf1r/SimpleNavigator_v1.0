#include "ants_logic.h"

AntsLogic::AntsLogic(const Graph &graph) : graph_(graph) {
  pheromone_.InitWithNumber(graph.GetSize(), 0.2);
  graph_size_ = graph_.GetSize();
}

TsmResult AntsLogic::SolveSalesmansProblem() {
  int counter = 0;

  TsmResult path;
  path.distance = INFINITY;
  CreateAnts();

  while (counter++ != kMaxLoopsWithNoGains_) {
    AdjMatrix local_pheromone_update;
    local_pheromone_update.InitWithNumber(graph_size_, 0);

    for (auto &ant : ants_) {
      // ant runs while he still can
      while (ant.GetMove()) {
        ant.AntMove(graph_, pheromone_, kAlpha_, kBeta_);
      }
      // compare ant result to best
      TsmResult ant_path = ant.GetPath();
      if ((int)ant_path.vertices.size() == graph_size_ + 1) {
        if (ant.GetPath().distance < path.distance) {
          path = std::move(ant.GetPath());
          counter = 0;
        }
        // calculate pheromone delta for every edge
        double pheromone_delta = kQ_ / ant_path.distance;
        for (int i = 0; i < graph_size_; ++i) {
          local_pheromone_update(ant_path.vertices[i],
                                 ant_path.vertices[i + 1]) += pheromone_delta;
        }
      }
    }

    UpdateGlobalPheromone(local_pheromone_update);
    BrainwashAnts();
  }

  return path;
}

void AntsLogic::CreateAnts() {
  ants_.reserve(graph_size_);

  for (int i = 0; i < graph_size_; ++i) {
    ants_.push_back(Ant(i));
  }
}

void AntsLogic::BrainwashAnts() {
  for (int i = 0; i < graph_size_; ++i) {
    ants_[i].BrainwashAnt();
  }
}

void AntsLogic::UpdateGlobalPheromone(const AdjMatrix &lpu) {
  int size = graph_.GetSize();
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i == j) continue;
      pheromone_(i, j) = kEvap_ * pheromone_(i, j) + lpu(i, j);
      if (pheromone_(i, j) < 0.2) pheromone_(i, j) = 0.2;
    }
  }
}
