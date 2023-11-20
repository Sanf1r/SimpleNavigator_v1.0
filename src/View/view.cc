#include "view.h"

View::View(Controller* c) : c_(c) {}

void View::DisplayMenu() {
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

int View::PerformChoice() {
  int choice;
  std::cout << "Input a menu item digit: ";
  std::cin >> choice;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

void View::StartEventLoop() {
  std::string path;
  bool is_load = false;
  while (true) {
    DisplayMenu();

    switch ((Choice)PerformChoice()) {
      case LOAD:
        std::cout << "Enter path to file: " << std::endl;
        std::cin >> path;
        if (c_->LoadGraphFromFile(path)) {
          std::cout << "Graph is successfully loaded!" << std::endl;
          is_load = true;
        } else {
          std::cout << "Something wrong with a file path!" << std::endl;
        }
        break;

      case BREADTH:
        if (LoadCheck(is_load)) Bfs();
        break;

      case DEPTH:
        if (LoadCheck(is_load)) Dfs();
        break;

      case SHORT1:
        if (LoadCheck(is_load)) Dijkstra();
        break;

      case SHORT2:
        if (LoadCheck(is_load)) FloWa();
        break;

      case TREE:
        if (LoadCheck(is_load)) Msp();
        break;

      case TSP:
        if (LoadCheck(is_load)) Tsp();
        break;

      case EXIT:
        exit(1);

      default:
        std::cout << "Wrong menu item number!" << std::endl;
        continue;
    }
  }
}

bool View::Input(int* num_1, int* num_2) {
  int size = c_->GetSize();
  std::cin >> *num_1;
  std::cin >> *num_2;
  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  if ((*num_1 > size || *num_1 < 1) || (*num_2 > size || *num_2 < 1)) {
    return false;
  }
  return true;
}

bool View::Input(int* num_1) {
  int size = c_->GetSize();
  std::cin >> *num_1;
  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  if ((*num_1 > size || *num_1 < 1)) {
    return false;
  }
  return true;
}

bool View::LoadCheck(bool flag) {
  if (flag) return true;
  std::cout << "You need to load graph first!" << std::endl;
  return false;
}

void View::Bfs() {
  std::cout << "=========" << std::endl;
  std::cout << " BREADTH-FIRST SEARCH " << std::endl;
  std::cout << "=========" << std::endl;
  int num = 0;
  std::cout << "Enter start vertex number: " << std::endl;
  if (Input(&num)) {
    std::vector<int> res_bfs = c_->BreadthFirstSearch(num);
    for (auto& data : res_bfs) std::cout << data << " ";
    std::cout << std::endl;
  } else {
    std::cout << "You enter wrong vertex number!" << std::endl;
  }
}

void View::Dfs() {
  std::cout << "=========" << std::endl;
  std::cout << " DEPTH-FIRST SEARCH " << std::endl;
  std::cout << "=========" << std::endl;
  int num = 0;
  std::cout << "Enter start vertex number: " << std::endl;
  if (Input(&num)) {
    std::vector<int> res_dfs = c_->DepthFirstSearch(num);
    for (auto& data : res_dfs) std::cout << data << " ";
    std::cout << std::endl;
  } else {
    std::cout << "You enter wrong vertex number!" << std::endl;
  }
}

void View::Dijkstra() {
  std::cout << "=========" << std::endl;
  std::cout << " DIJKSTRA'S ALGORITHM " << std::endl;
  std::cout << "=========" << std::endl;
  int num_1 = 0, num_2 = 0;

  std::cout << "Enter start and finish vertex numbers: " << std::endl;
  if (Input(&num_1, &num_2)) {
    long res_dij = c_->GetShortestPathBetweenVertices(num_1, num_2);
    if (res_dij == -1) {
      std::cout << "Path does not exist!" << std::endl;
    } else {
      std::cout << "Shortest path length is " << res_dij << std::endl;
    }

  } else {
    std::cout << "You enter wrong vertex numbers!" << std::endl;
  }
}

void View::FloWa() {
  std::cout << "=========" << std::endl;
  std::cout << " FLOYD-WARSHALL ALGORITHM " << std::endl;
  std::cout << "=========" << std::endl;

  auto res_flowa = c_->GetShortestPathsBetweenAllVertices();

  res_flowa.Print();
}

void View::Msp() {
  std::cout << "=========" << std::endl;
  std::cout << " MINIMUM SPANNING TREE " << std::endl;
  std::cout << "=========" << std::endl;
  if (!c_->UndirectedCheck()) {
    std::cout << "Loaded graph is not undirected!" << std::endl;
  } else {
    std::vector<std::vector<double>> tree_res =
        std::move(c_->GetLeastSpanningTree());
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

void View::Tsp() {
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
