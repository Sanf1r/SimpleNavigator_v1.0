#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "model.h"

int main() {
  Graph one;
  AntsLogic al(one);
  // std::vector<std::vector<double>> res = GetLeastSpanningTree(one);

  // for (int i = 0; i < 7; ++i) {
  //   for (int j = 0; j < 7; ++j) {
  //     std::cout << res[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  TsmResult res = al.SolveSalesmansProblem();

  for (int i = 0; i < (int)res.vertices.size(); ++i) {
    std::cout << res.vertices[i] + 1 << " ";
  }
  std::cout << std::endl;

  std::cout << res.distance << std::endl;

  return 0;
}