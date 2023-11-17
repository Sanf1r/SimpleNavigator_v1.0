#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "./model.h"

class Controller {
 public:
  Controller() = delete;
  explicit Controller(Model* m) : model_(m){};

  TsmResult SolveTravelingSalesmanProblem() {
    return model_->SolveTravelingSalesmanProblem();
  }

  std::vector<std::vector<double>> GetLeastSpanningTree() {
    return model_->GetLeastSpanningTree();
  }

  std::vector<int> BreadthFirstSearch(int num) {
    return model_->BreadthFirstSearch(num);
  }

  std::vector<int> DepthFirstSearch(int num) {
    return model_->DepthFirstSearch(num);
  }

  long GetShortestPathBetweenVertices(int vertex1, int vertex2) {
    return model_->GetShortestPathBetweenVertices(vertex1, vertex2);
  }

  AdjMatrix GetShortestPathsBetweenAllVertices() {
    return model_->GetShortestPathsBetweenAllVertices();
  }

  bool LoadGraph(const std::string& path) { return model_->LoadGraph(path); }

  bool UndirectedCheck() { return model_->UndirectedCheck(); }

  int GetSize() { return model_->GetSize(); }

 private:
  Model* model_;
};

#endif  //  CONTROLLER_H_
