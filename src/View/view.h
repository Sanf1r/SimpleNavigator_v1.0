#ifndef VIEW_H_
#define VIEW_H_

#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../Controller/controller.h"

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
  explicit View(Controller* c);
  void DisplayMenu();

  int PerformChoice();
  void StartEventLoop();

 private:
  Controller* c_;

  bool Input(int* num_1, int* num_2);

  bool Input(int* num_1);

  bool LoadCheck(bool flag);

  void Bfs();

  void Dfs();

  void Dijkstra();

  void FloWa();

  void Msp();

  void Tsp();
};

#endif  //  VIEW_H_
