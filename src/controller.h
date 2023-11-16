#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "./model.h"

class Controller {
 public:
  explicit Controller(Model* m) : model_(m){};

  TsmResult SolveTravelingSalesmanProblem() {
    return model_->SolveTravelingSalesmanProblem();
  }

  std::vector<std::vector<double>> GetLeastSpanningTree() {
    return model_->GetLeastSpanningTree();
  }

  void LoadGraph(const std::string& path) { return model_->LoadGraph(path); }

 private:
  Model* model_;
};

#endif  //  CONTROLLER_H_
