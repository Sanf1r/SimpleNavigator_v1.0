#ifndef ANT_H_
#define ANT_H_

class Ant {
 public:
  explicit Ant(int start) : start_location(start), current_location(start) {}

  void MakeChoice(const Graph &graph,
                  const std::vector<std::vector<double>> &pheromone_map,
                  double a, double b) {
    if (path.vertices.empty()) {
      path.vertices.push_back(current_location);
      visited.push_back(current_location);
    }

    std::vector<int> neighbor_vertexes = getNeighborVertexes(graph);

    if (neighbor_vertexes.empty()) {
      can_continue = false;
      if (graph(current_location, start_location) != inf) {
        path.vertices.push_back(start_location);
        path.distance += graph(current_location, start_location);
      }
      return;
    }

    std::vector<double> choosing_probability(neighbor_vertexes.size());

    // Подсчет вероятности перехода муравья из одной вершины в другую
    std::vector<double> wish;
    std::vector<double> probability;
    double summary_wish = 0.0f;
    for (auto v : neighbor_vertexes) {
      double t = pheromone_map[current_location][v];
      double w = graph(current_location, v);
      double n = 1 / w;
      wish.push_back(std::pow(t, a) * std::pow(n, b));
      summary_wish += wish.back();
    }

    for (std::size_t neighbor = 0; neighbor != neighbor_vertexes.size();
         ++neighbor) {
      probability.push_back(wish[neighbor] / summary_wish);
      if (neighbor == 0)
        choosing_probability[neighbor] = probability.back();
      else
        choosing_probability[neighbor] =
            choosing_probability[neighbor - 1] + probability.back();
    }

    // Определение следующей вершины, которую посетит муравей
    std::size_t next_vertex = 0;
    double choose = getRandomChoice();

    for (std::size_t n = 0; n != neighbor_vertexes.size(); ++n) {
      if (choose <= choosing_probability[n]) {
        next_vertex = neighbor_vertexes[n];
        break;
      }
    }

    path.vertices.push_back(next_vertex);
    path.distance += graph(current_location, next_vertex);
    visited.push_back(next_vertex);
    current_location = next_vertex;
  }

  double getRandomChoice() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> gen(0, 1);
    return gen(rng);
  }

  std::vector<int> getNeighborVertexes(const Graph &graph) {
    std::vector<int> vertexes;
    for (int to = 0; to < graph.GetSize(); ++to) {
      bool edge_is_exist = graph(current_location, to) != inf;
      bool vertex_is_unvisited =
          std::find(visited.begin(), visited.end(), to) == visited.end();
      if (edge_is_exist && vertex_is_unvisited) vertexes.push_back(to);
    }
    return vertexes;
  }

  bool CanYou() { return can_continue; }

  TsmResult &GetPath() { return path; }

 private:
  TsmResult path;

  std::vector<int> visited;
  int start_location = 0, current_location = 0;
  bool can_continue = true;
};

#endif  //  ANT_H_