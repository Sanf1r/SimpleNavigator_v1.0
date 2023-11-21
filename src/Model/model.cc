#include "model.h"

namespace s21 {

TsmResult Model::SolveTravelingSalesmanProblem() {
  return ga_.SolveSalesmansProblem(graph_);
}

std::vector<std::vector<double>> Model::GetLeastSpanningTree() {
  return ga_.GetLeastSpanningTree(graph_);
}

std::vector<int> Model::BreadthFirstSearch(int num) {
  return ga_.BreadthFirstSearch(graph_, num);
}

std::vector<int> Model::DepthFirstSearch(int num) {
  return ga_.DepthFirstSearch(graph_, num);
}

long Model::GetShortestPathBetweenVertices(int vertex1, int vertex2) {
  return ga_.GetShortestPathBetweenVertices(graph_, vertex1, vertex2);
}

AdjMatrix Model::GetShortestPathsBetweenAllVertices() {
  return ga_.GetShortestPathsBetweenAllVertices(graph_);
}

bool Model::LoadGraphFromFile(const std::string& path) {
  return graph_.LoadGraphFromFile(path);
}

bool Model::ExportGraphToDot(const std::string& path) {
  return graph_.ExportGraphToDot(path);
}

bool Model::UndirectedCheck() { return ga_.UndirectedCheck(graph_); }

int Model::GetSize() { return graph_.GetSize(); }

}  // namespace s21
