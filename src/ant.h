#ifndef ANT_H_
#define ANT_H_

class Ant {
 public:
  Ant() = delete;

  explicit Ant(int start) : start_location(start), current_location(start) {}

  void AntMove(const Graph &graph, const AdjMatrix &pheromone_map, double a,
               double b) {
    // start run
    if (path.vertices.empty()) {
      path.vertices.push_back(current_location);
      visited.insert(current_location);
    }

    // get neighbors
    std::vector<int> neighbor_vertexes = getNeighborVertexes(graph);

    // if nowhere to run
    if (neighbor_vertexes.empty()) {
      can_move = false;
      if (graph(current_location, start_location) != inf) {
        path.vertices.push_back(start_location);
        path.distance += graph(current_location, start_location);
      }
      return;
    }

    MakeRoulette(neighbor_vertexes, pheromone_map, graph, a, b);

    // casino
    int next_vertex = 0;
    double choose = getRandomChoice();
    int index =
        std::lower_bound(probability.begin(), probability.end(), choose) -
        probability.begin();
    next_vertex = neighbor_vertexes[index];

    // add, calculate and repeat
    path.vertices.push_back(next_vertex);
    path.distance += graph(current_location, next_vertex);
    visited.insert(next_vertex);
    current_location = next_vertex;
  }

  bool GetMove() { return can_move; }

  TsmResult &GetPath() { return path; }

 private:
  TsmResult path;

  std::set<int> visited;
  std::vector<double> probability;
  int start_location = 0, current_location = 0;
  bool can_move = true;

  double getRandomChoice() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> gen(0, 1);
    return gen(rng);
  }

  std::vector<int> getNeighborVertexes(const Graph &graph) {
    std::vector<int> vertexes;
    for (int to = 0; to < graph.GetSize(); ++to) {
      if (graph(current_location, to) != inf &&
          visited.find(to) == visited.end()) {
        vertexes.push_back(to);
      }
    }
    return vertexes;
  }

  void MakeRoulette(std::vector<int> &neighbor_vertexes,
                    const AdjMatrix &pheromone_map, const Graph &graph,
                    double a, double b) {
    // calculate wishes for vertexes
    probability.clear();
    std::vector<double> wish;
    double summary_wish = 0.0f;
    for (auto &v : neighbor_vertexes) {
      double t = pheromone_map(current_location, v);
      double n = std::pow(graph(current_location, v), -1);
      wish.push_back(std::pow(t, a) * std::pow(n, b));
      summary_wish += wish.back();
    }

    // make roulette wheel
    int neighbor_size = neighbor_vertexes.size();
    for (int i = 0; i < neighbor_size; ++i) {
      probability.push_back(wish[i] / summary_wish);
      if (i != 0) probability[i] += probability[i - 1];
    }
  }
};

#endif  //  ANT_H_