#ifndef ANTS_LOGIC_H_
#define ANTS_LOGIC_H_

class AntsLogic {
 public:
  explicit AntsLogic(const Graph &graph) : graph_(graph) {
    pheromone_.InitWithNumber(graph.GetSize(), 0.2);
    // pheromone_.GetData().insert(pheromone_.GetData().end(),
    //                             graph.GetData().begin(),
    //                             graph.GetData().end());
  }

  TsmResult SolveSalesmansProblem() {
    // if (graph_.IsEmpty())
    //      return {};

    const int kVertexesCount = graph_.GetSize();
    int counter = 0;

    TsmResult path;
    path.distance = inf;

    while (counter++ != kMaxLoopsWithNoGains) {
      AdjMatrix local_pheromone_update;
      local_pheromone_update.InitWithNumber(kVertexesCount, 0);

      CreateAnts();

      for (auto &ant : ants_) {
        // ant runs
        while (ant.GetMove()) {
          ant.AntMove(graph_, pheromone_, kAlpha_, kBeta_);
        }
        // compare dist
        TsmResult ant_path = ant.GetPath();
        if ((int)ant_path.vertices.size() == kVertexesCount + 1) {
          if (path.distance > ant.GetPath().distance) {
            path = std::move(ant.GetPath());
            counter = 0;
          }

          double pheromone_shift = kQ_ / ant_path.distance;
          for (int i = 0; i < kVertexesCount; ++i) {
            local_pheromone_update(ant_path.vertices[i],
                                   ant_path.vertices[i + 1]) += pheromone_shift;
          }
        }
      }

      UpdateGlobalPheromone(local_pheromone_update);
    }

    return path;
  }

 private:
  Graph graph_;
  AdjMatrix pheromone_;

  const int kMaxLoopsWithNoGains = 2000;
  const double kAlpha_ = 2.0;
  const double kBeta_ = 1.0;
  const double kQ_ = 1.0;
  const double kEvap_ = 0.8;

  std::vector<Ant> ants_;

  void CreateAnts() {
    ants_.clear();
    const int kAntsCount = graph_.GetSize();
    ants_.reserve(kAntsCount);

    for (int i = 0; i < kAntsCount; ++i) {
      ants_.push_back(Ant(i));
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