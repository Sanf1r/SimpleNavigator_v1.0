#ifndef ANTS_LOGIC_H_
#define ANTS_LOGIC_H_

class AntsLogic {
 public:
  AntsLogic() = delete;
  explicit AntsLogic(const Graph &graph) : graph_(graph) {
    pheromone_.InitWithNumber(graph.GetSize(), 0.2);
    graph_size_ = graph_.GetSize();
  }

  TsmResult SolveSalesmansProblem() {
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

  void CreateAnts() {
    ants_.reserve(graph_size_);

    for (int i = 0; i < graph_size_; ++i) {
      ants_.push_back(Ant(i));
    }
  }

  void BrainwashAnts() {
    for (int i = 0; i < graph_size_; ++i) {
      ants_[i].BrainwashAnt();
    }
  }

  void UpdateGlobalPheromone(const AdjMatrix &lpu) {
    int size = graph_.GetSize();
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (i == j) continue;
        pheromone_(i, j) = kEvap_ * pheromone_(i, j) + lpu(i, j);
        if (pheromone_(i, j) < 0.2) pheromone_(i, j) = 0.2;
      }
    }
  }
};

#endif  //  ANTS_LOGIC_H_