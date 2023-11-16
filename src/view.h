#ifndef VIEW_H_
#define VIEW_H_

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
    TsmResult res;
    std::string path;
    while (true) {
      displayMenu();

      switch ((Choice)performChoice()) {
        case LOAD:
          std::cout << "Enter path to file: " << std::endl;
          std::cin >> path;
          c_->LoadGraph(path);
          break;

        case BREADTH:
          std::cout << "You pick 2" << std::endl;
          break;

        case DEPTH:
          std::cout << "You pick 3" << std::endl;
          break;

        case SHORT1:
          std::cout << "You pick 4" << std::endl;
          break;

        case SHORT2:
          std::cout << "You pick 5" << std::endl;
          break;

        case TREE:
          std::cout << "You pick 6" << std::endl;
          break;

        case TSP:
          res = c_->SolveTravelingSalesmanProblem();
          std::cout << "TSP problem solved!" << std::endl;
          std::cout << "Path - ";
          for (int i = 0; i < (int)res.vertices.size(); ++i) {
            std::cout << res.vertices[i] + 1 << " ";
          }
          std::cout << std::endl;
          std::cout << "Total distance - ";
          std::cout << res.distance << std::endl;
          // std::cout << "time - " << total << " seconds" << std::endl;
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
};

#endif  //  VIEW_H_
