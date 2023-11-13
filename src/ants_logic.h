#ifndef ANTS_LOGIC_H_
#define ANTS_LOGIC_H_

class AntsLogic {
 public:
  explicit AntsLogic(const Graph &graph)
      : graph_(graph), kQ_(0.015 * graph.GetSize()) {
    // const std::size_t kVertexesCount = graph_.getVertexesCount();
    // Matrix<double> matrix(kVertexesCount);
    // for (std::size_t row = 0; row != kVertexesCount; ++row)
    //   for (std::size_t col = 0; col != kVertexesCount; ++col)
    //     if (row != col) matrix(row, col) = kPheromone0_;

    pheromone_ = graph.GetData();
  }

  TsmResult SolveSalesmansProblem() {
    // if (graph_.IsEmpty())
    //      return {};

    constexpr std::size_t kMaxIterationsWithoutImprovement = 100;
    const std::size_t kVertexesCount = graph_.GetSize();
    std::size_t counter = 0;

    TsmResult path;
    path.distance = inf;

    while (counter++ != kMaxIterationsWithoutImprovement) {
      std::vector<std::vector<double>> local_pheromone_update(kVertexesCount);
      for (size_t i = 0; i < kVertexesCount; ++i) {
        local_pheromone_update[i].resize(11);
      }

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
            local_pheromone_update[ant_path.vertices[v]]
                                  [ant_path.vertices[v + 1]] +=
                kQ_ / ant_path.distance;
          }
        }
      }

      UpdateGlobalPheromone(local_pheromone_update);
    }
    return path;
  }

 private:
  Graph graph_;
  std::vector<std::vector<double>> pheromone_;

  const double kAlpha_ = 1.0;
  const double kBeta_ = 2.0;
  const double kPheromone0_ = 1;
  const double kQ_;
  const double kEvaporation_ = 0.2;

  std::vector<Ant> ants_;

  void CreateAnts() {
    const auto kAntsCount = graph_.GetSize();
    // ants_.resize(kAntsCount);

    for (int i = 0; i < kAntsCount; ++i) {
      ants_.push_back(Ant(i));
    }
  }
  void UpdateGlobalPheromone(const std::vector<std::vector<double>> &lpu) {
    int size = lpu.size();
    for (int from = 0; from < size; ++from) {
      for (int to = 0; to < size; ++to) {
        pheromone_[from][to] =
            (1 - kEvaporation_) * pheromone_[from][to] + lpu[from][to];
        if (pheromone_[from][to] < 0.01 and from != to)
          pheromone_[from][to] = 0.01;
      }
    }
  }
};

#endif  //  ANTS_LOGIC_H_