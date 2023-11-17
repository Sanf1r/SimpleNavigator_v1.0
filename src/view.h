#ifndef VIEW_H_
#define VIEW_H_

#include <chrono>
#include <iostream>
#include <string>

enum Choice {
  LOAD = 1,
  BREADTH = 2,
  DEPTH = 3,
  SHORT1 = 4,
  SHORT2 = 5,
  TREE = 6,
  TSP = 7,
  EXIT = 0
};

class View {
 public:
  explicit View(Controller* c) : c_(c){};
  void displayMenu() {
    std::cout << "=========" << std::endl;
    std::cout << " M E N U " << std::endl;
    std::cout << "=========" << std::endl;
    std::cout << "1. Load the original graph from a file" << std::endl;
    std::cout << "2. Graph traversal in breadth" << std::endl;
    std::cout << "3. Graph traversal in depth" << std::endl;
    std::cout << "4. Searching for the shortest path between any two vertices"
              << std::endl;
    std::cout << "5. Searching for the shortest paths between all pairs of "
                 "vertices in the graph"
              << std::endl;
    std::cout << "6. Searching for the minimal spanning tree in the graph"
              << std::endl;
    std::cout << "7. Solving the traveling salesman problem" << std::endl;
    std::cout << "0. Quit" << std::endl << std::endl;
  }

  int performChoice() {
    int choice;
    std::cout << "Input a menu item digit: ";
    std::cin >> choice;
    return choice;
  }

  void startEventLoop() {
    std::string path;
    while (true) {
      displayMenu();

      switch ((Choice)performChoice()) {
        case LOAD:
          std::cout << "Enter path to file: " << std::endl;
          std::cin >> path;
          if (c_->LoadGraph(path)) {
            std::cout << "Graph is successfully loaded!" << std::endl;
          } else {
            std::cout << "Something wrong with a file path!" << std::endl;
          }
          break;

        case BREADTH:
          Bfs();
          break;

        case DEPTH:
          Dfs();
          break;

        case SHORT1:
          Dijkstra();
          break;

        case SHORT2:
          FloWa();
          break;

        case TREE:
          Msp();
          break;

        case TSP:
          Tsp();
          break;

        case EXIT:
          exit(1);

        default:
          std::cout << "Wrong menu item number!" << std::endl;
          continue;
      }
    }
  }

 private:
  Controller* c_;

  void Tsp() {
    TsmResult tsm_res;
    std::cout << "=========" << std::endl;
    std::cout << " TRAVELLING SALESMAN PROBLEM " << std::endl;
    std::cout << "=========" << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    tsm_res = std::move(c_->SolveTravelingSalesmanProblem());
    auto t2 = std::chrono::high_resolution_clock::now();
    auto total =
        std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    if (tsm_res.distance != INFINITY) {
      std::cout << "Travelling salesman problem solved!" << std::endl;
      std::cout << "Path - ";
      for (int i = 0; i < (int)tsm_res.vertices.size(); ++i) {
        std::cout << tsm_res.vertices[i] + 1 << " ";
      }
      std::cout << std::endl;
      std::cout << "Total distance - ";
      std::cout << tsm_res.distance << std::endl;
      std::cout << "Time to solve - " << total << " seconds" << std::endl;
    } else {
      std::cout << "Travelling salesman problem cannot be solved for "
                   "this graph!"
                << std::endl;
    }
  }

  void Msp() {
    std::vector<std::vector<double>> tree_res;
    std::cout << "=========" << std::endl;
    std::cout << " MINIMUM SPANNING TREE " << std::endl;
    std::cout << "=========" << std::endl;
    if (!c_->UndirectedCheck()) {
      std::cout << "Loaded graph is not undirected!" << std::endl;
    } else {
      tree_res = std::move(c_->GetLeastSpanningTree());
      std::cout << "Minimum spanning tree found!" << std::endl;
      std::cout << "The adjacency matrix for the minimum spanning tree "
                   "presented below:"
                << std::endl;
      for (int i = 0; i < (int)tree_res.size(); ++i) {
        for (int j = 0; j < (int)tree_res.size(); ++j) {
          if (tree_res[i][j] == INFINITY)
            std::cout << "0 ";
          else
            std::cout << tree_res[i][j] << " ";
        }
        std::cout << std::endl;
      }
    }
  }

  void Bfs() {
    std::cout << "BFS" << std::endl;
    int num = 0;
    std::cout << "Enter start vertex number: " << std::endl;
    std::cin >> num;

    std::vector<int> res_bfs = c_->BreadthFirstSearch(num);
    for (auto& data : res_bfs) std::cout << data << " ";
    std::cout << std::endl;
  }

  void Dfs() {
    std::cout << "DFS" << std::endl;
    int num = 0;
    std::cout << "Enter start vertex number: " << std::endl;
    std::cin >> num;

    std::vector<int> res_dfs = c_->DepthFirstSearch(num);
    for (auto& data : res_dfs) std::cout << data << " ";
    std::cout << std::endl;
  }

  void Dijkstra() {
    std::cout << "Dijkstra" << std::endl;
    int num_1 = 0, num_2 = 0;

    std::cout << "Enter start and finish vertex numbers: " << std::endl;
    std::cin >> num_1 >> num_2;

    long res_dij = c_->GetShortestPathBetweenVertices(num_1, num_2);

    std::cout << res_dij << std::endl;
  }

  void FloWa() {
    std::cout << "FloWa" << std::endl;

    auto res_flowa = c_->GetShortestPathsBetweenAllVertices();

    res_flowa.Print();
  }
};

#endif  //  VIEW_H_
