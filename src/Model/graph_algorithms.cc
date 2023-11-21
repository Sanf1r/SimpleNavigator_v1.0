#include "graph_algorithms.h"

namespace s21 {

/**
 * @brief Поиск в ширину в графе от заданной вершины. Функция
 * возвращает массив, содержащий в себе обойдённые вершины в порядке их
 * обхода. При реализации этой функции использовалась самописная
 * структуру данных очередь.
 *
 * @param graph
 * @param start_vertex
 */
std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int start_vertex) {
  std::vector<int> visited(graph.GetSize(), -1);
  std::vector<int> visited_order;
  queue<std::pair<int, int>> stack_order;
  std::pair<int, int> node;
  start_vertex--;

  stack_order.push({start_vertex, 1});
  while (!stack_order.empty()) {
    node = stack_order.back();
    stack_order.pop();

    if (visited.at(node.first) == 1) continue;
    visited.at(node.first) = 1;
    visited_order.push_back(node.first + 1);

    if (node.second == 1) {
      for (int i = 0; i < graph.GetSize(); ++i) {
        if (graph(node.first, i) != INFINITY) {
          stack_order.push({i, 1});
        }
      }
    }
  }
  return visited_order;
}

/**
 * @brief Нерекурентный поиск в глубину в графе от заданной вершины.
 * Функция возвращает массив, содержащий в себе обойдённые
 * вершины в порядке их обхода. При реализации этой функции
 * использовалась самописную структуру данных стек.
 *
 * @param graph
 * @param start_vertex
 */
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int start_vertex) {
  std::vector<int> visited(graph.GetSize(), -1);
  std::vector<int> visited_order;
  stack<std::pair<int, int>> stack_order;

  int vertex_now = start_vertex - 1;
  visited.at(vertex_now) = 1;
  stack_order.push({vertex_now, 2});

  while (!stack_order.empty()) {
    if (stack_order.top().second == 2) {
      stack_order.top().second = 1;
      for (int i = 0; i < graph.GetSize(); ++i) {
        if (graph(vertex_now, i) != INFINITY && visited.at(i) != 1) {
          stack_order.push({i, 2});
          visited.at(i) = 1;
        }
      }
      if (stack_order.size() > 0) {
        vertex_now = stack_order.top().first;
      } else {
        break;
      }
    } else if (stack_order.top().second == 1) {
      stack_order.top().second = 0;
      visited_order.push_back(stack_order.top().first + 1);
      stack_order.pop();
      if (!stack_order.empty()) {
        vertex_now = stack_order.top().first;
      }
    } else if (stack_order.top().second == 0) {
      visited_order.push_back(stack_order.top().first + 1);
      stack_order.pop();
      if (!stack_order.empty()) {
        vertex_now = stack_order.top().first;
      }
    }
  }
  std::reverse(visited_order.begin(), visited_order.end());
  return visited_order;
}

/**
 * @brief Поиск кратчайшего пути между двумя вершинами в графе с использованием
 * алгоритма Дейкстры. Функция принимает на вход номера двух вершин и
 * возвращает численный результат, равный наименьшему расстоянию между ними
 *
 * @param graph
 * @param vertex1
 * @param vertex2
 * @return long int
 */
long GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& graph,
                                                     int vertex1, int vertex2) {
  int vertex_count = graph.GetSize();
  vertex1--;
  vertex2--;

  std::vector<double> dist(vertex_count, INFINITY);
  dist.at(vertex1) = 0;
  std::vector<int> visited(vertex_count, -1);

  if (vertex1 == vertex2) return 0;
  for (int i = 0; i < vertex_count; ++i) {
    int nearest = -1;
    for (int j = 0; j < vertex_count; ++j) {
      if (visited.at(j) != 1 &&
          (nearest == -1 || dist.at(nearest) > dist.at(j))) {
        nearest = j;
      }
    }

    if (dist.at(nearest) == INFINITY) return -1;
    visited.at(nearest) = 1;
    for (int i2 = 0; i2 < vertex_count; ++i2) {
      if (graph(nearest, i2) == INFINITY) continue;
      dist.at(i2) =
          std::min(dist.at(i2), dist.at(nearest) + graph(nearest, i2));
    }
  }
  return dist[vertex2];
}

/**
 * @brief Поиск кратчайших путей между всеми парами вершин в графе с
 * использованием алгоритма Флойда-Уоршелла. В качестве результата
 * функция возвращает матрицу кратчайших путей между всеми вершинами графа
 *
 * @param graph
 * @return std::vector<std::vector<int>>
 */
AdjMatrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    const Graph& graph) {
  int vertex_count = graph.GetSize();
  AdjMatrix dist;
  dist.Init(vertex_count);
  dist.GetData().insert(dist.GetData().end(), graph.GetData().begin(),
                        graph.GetData().end());

  for (int v = 0; v < vertex_count; ++v) {
    for (int a = 0; a < vertex_count; ++a) {
      for (int b = 0; b < vertex_count; ++b) {
        if (a == b) dist(a, b) = 0;
        if (dist(a, v) != INFINITY && dist(v, b) != INFINITY) {
          dist(a, b) = std::min(dist(a, b), dist(a, v) + dist(v, b));
        }
      }
    }
  }
  return dist;
}

/**
 * @brief Поиск наименьшего остовного дерева в графе с помощью
 * алгоритма Прима. В качестве результата функция возвращает
 * матрицу смежности для минимального остовного дерева.
 *
 * @param graph
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<double>> GraphAlgorithms::GetLeastSpanningTree(
    const Graph& graph) {
  std::vector<std::vector<double>> result;
  int graph_size = graph.GetSize();
  result.resize(graph_size);
  for (int i = 0; i < graph_size; ++i) {
    result[i].resize(graph_size, INFINITY);
  }

  std::set<int> visited;
  std::set<int> unvisited;

  int from = 0, to = 0;

  for (int i = 0; i < graph_size; ++i) {
    unvisited.insert(i);
  }

  int random_index = Random(graph_size);

  visited.insert(random_index);
  unvisited.erase(random_index);

  while (!unvisited.empty()) {
    double min = INFINITY;
    for (auto i = visited.begin(); i != visited.end(); ++i) {
      for (auto j = unvisited.begin(); j != unvisited.end(); ++j) {
        bool not_INFINITY = graph(*i, *j) != INFINITY;
        if (not_INFINITY && graph(*i, *j) < min) {
          min = graph(*i, *j);
          from = *i;
          to = *j;
        }
      }
    }

    result[to][from] = result[from][to] = min;
    visited.insert(to);
    unvisited.erase(to);
  }
  return result;
}

/**
 * @brief Решение задачи коммивояжера с помощью муравьиного алгоритма.
 * Находим самый выгодный (короткий) маршрут, проходящий
 * через все вершины графа хотя бы по одному разу с последующим
 * возвратом в исходную вершину. В качестве результата функция
 * возвращает структуру TsmResult.
 *
 * @param graph
 * @return TsmResult
 */
TsmResult GraphAlgorithms::SolveSalesmansProblem(const Graph& graph) {
  AntsLogic al_(graph);
  return al_.SolveSalesmansProblem();
}

bool GraphAlgorithms::UndirectedCheck(const Graph& graph) {
  bool res = true;
  int graph_size = graph.GetSize();
  for (auto i = 0; i < graph_size; ++i) {
    for (auto j = i; j < graph_size; ++j) {
      if (graph(i, j) != graph(j, i)) {
        res = false;
      }
    }
  }
  return res;
}

int GraphAlgorithms::Random(int size) {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> gen(0, size - 1);
  return gen(rng);
}

}  // namespace s21
