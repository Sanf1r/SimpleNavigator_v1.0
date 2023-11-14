#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "model.h"

int main() {
  Graph one;
  // std::string path = "/Users/morfinov/GHNavi/src/test.txt";
  // std::string path = "/Users/morfinov/GHNavi/src/tsp.txt";
  std::string path = "/Users/morfinov/GHNavi/src/tsp2.txt";
  one.LoadGraph(path);

  AntsLogic al(one);

  auto t1 = std::chrono::high_resolution_clock::now();

  TsmResult res = al.SolveSalesmansProblem();

  auto t2 = std::chrono::high_resolution_clock::now();
  auto total =
      std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

  for (int i = 0; i < (int)res.vertices.size(); ++i) {
    std::cout << res.vertices[i] + 1 << " ";
  }
  std::cout << std::endl;

  std::cout << res.distance << std::endl;
  std::cout << "time - " << total << " seconds" << std::endl;

  return 0;
}