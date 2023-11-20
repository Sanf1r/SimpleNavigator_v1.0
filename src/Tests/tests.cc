#include <gtest/gtest.h>

#include "../Model/model.h"

namespace {
Model test;
std::string path = "./Tests/test_graph.txt";
std::string path_to_save = "./Tests/dot_graph.dot";

TEST(NavigatorTest, 01) {
  test.LoadGraphFromFile(path);
  test.ExportGraphToDot(path_to_save);
}

TEST(NavigatorTest, 02) {
  test.BreadthFirstSearch(1);
  test.DepthFirstSearch(1);
}

TEST(NavigatorTest, 03) {
  test.GetShortestPathBetweenVertices(1, 5);
  AdjMatrix res = test.GetShortestPathsBetweenAllVertices();
  res.Print();
}

TEST(NavigatorTest, 04) {
  test.UndirectedCheck();
  test.GetLeastSpanningTree();
}

TEST(NavigatorTest, 05) { test.SolveTravelingSalesmanProblem(); }

}  // namespace
