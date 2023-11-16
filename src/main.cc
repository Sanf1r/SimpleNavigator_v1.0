#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "model.h"

int main() {
  Graph one;
  std::string path = "/Users/morfinov/GHNavi/src/test.txt";
  // std::string path = "/Users/morfinov/GHNavi/src/tsp.txt";
  // std::string path = "/Users/morfinov/GHNavi/src/test2.txt";
  // std::string path = "/Users/morfinov/GHNavi/src/bigone.txt";
  // std::string path =
  // "/Users/morfinov/GHNavi/src/examples/really_big_one.txt"; std::string path
  // = "/Users/morfinov/GHNavi/src/examples/tail.txt";
  one.LoadGraph(path);

  AntsLogic al(one);

  auto t1 = std::chrono::high_resolution_clock::now();

  TsmResult res = al.SolveSalesmansProblem();

  auto t2 = std::chrono::high_resolution_clock::now();
  auto total =
      std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

  if (res.distance == inf) {
    std::cout << "ERROR!" << std::endl;
    return 1;
  }

  for (int i = 0; i < (int)res.vertices.size(); ++i) {
    std::cout << res.vertices[i] + 1 << " ";
  }
  std::cout << std::endl;

  std::cout << res.distance << std::endl;
  std::cout << "time - " << total << " seconds" << std::endl;

  return 0;
}