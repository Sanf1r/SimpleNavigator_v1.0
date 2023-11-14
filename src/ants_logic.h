#ifndef ANTS_LOGIC_H_
#define ANTS_LOGIC_H_

class AntsLogic {
 public:
  explicit AntsLogic(const Graph &graph)
      : graph_(graph), kQ_(0.015 * graph.GetSize()) {
    pheromone_.GetData().insert(pheromone_.GetData().end(),
                                graph.GetData().begin(), graph.GetData().end());
    pheromone_.SetJump(graph.GetSize());
  }

  TsmResult SolveSalesmansProblem() {
    // if (graph_.IsEmpty())
    //      return {};

    constexpr std::size_t kMaxIterationsWithoutImprovement = 5000;
    const std::size_t kVertexesCount = graph_.GetSize();
    std::size_t counter = 0;

    TsmResult path;
    path.distance = inf;

    while (counter++ != kMaxIterationsWithoutImprovement) {
      AdjMatrix local_pheromone_update;
      local_pheromone_update.init(kVertexesCount * kVertexesCount);
      local_pheromone_update.SetJump(kVertexesCount);

      CreateAnts();

      for (auto &ant : ants_) {
        // ant runs
        while (ant.CanYou()) {
          ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);
        }
        // compare dist
        auto ant_path = ant.GetPath();
        if (ant_path.vertices.size() == kVertexesCount + 1) {
          if (path.distance > ant.GetPath().distance) {
            path = std::move(ant.GetPath());
            counter = 0;
          }

          for (std::size_t v = 0; v != ant_path.vertices.size() - 1; ++v) {
            local_pheromone_update(ant_path.vertices[v],
                                   ant_path.vertices[v + 1]) +=
                kQ_ / ant_path.distance;
          }
        }
      }

      UpdateGlobalPheromone(local_pheromone_update);
    }

    // ants_.clear();
    // ants_.push_back(Ant(0));

    // while (ants_[0].CanYou()) {
    //   ants_[0].MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);
    // }

    // path = std::move(ants_[0].GetPath());
    return path;
  }

 private:
  Graph graph_;
  AdjMatrix pheromone_;

  const double kAlpha_ = 1.0;
  const double kBeta_ = 2.0;
  const double kPheromone0_ = 1;
  const double kQ_;
  const double kEvaporation_ = 0.2;

  std::vector<Ant> ants_;

  void CreateAnts() {
    ants_.clear();
    const int kAntsCount = graph_.GetSize();

    for (int i = 0; i < kAntsCount; ++i) {
      ants_.push_back(Ant(i));
    }
  }
  void UpdateGlobalPheromone(const AdjMatrix &lpu) {
    // int size = lpu.size();
    int size = graph_.GetSize();
    for (int from = 0; from < size; ++from) {
      for (int to = 0; to < size; ++to) {
        pheromone_(from, to) =
            (1 - kEvaporation_) * pheromone_(from, to) + lpu(from, to);
        if (pheromone_(from, to) < 0.01 and from != to)
          pheromone_(from, to) = 0.01;
      }
    }
  }
};

#endif  //  ANTS_LOGIC_H_