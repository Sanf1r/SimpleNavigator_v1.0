#ifndef ADJ_MATRIX_H_
#define ADJ_MATRIX_H_

#include <vector>

class AdjMatrix {
 public:
  AdjMatrix() {
    data_.resize(11);

    data_[0] = {inf, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18};
    data_[1] = {29, inf, 15, 29, 28, 40, 72, 21, 29, 41, 12};
    data_[2] = {20, 15, inf, 15, 14, 25, 81, 9, 23, 27, 13};
    data_[3] = {21, 29, 15, inf, 4, 12, 92, 12, 25, 13, 25};
    data_[4] = {16, 28, 14, 4, inf, 16, 94, 9, 20, 16, 22};
    data_[5] = {31, 40, 25, 12, 16, inf, 95, 24, 36, 3, 37};
    data_[6] = {100, 72, 81, 92, 94, 95, inf, 90, 101, 99, 84};
    data_[7] = {12, 21, 9, 12, 9, 24, 90, inf, 15, 25, 13};
    data_[8] = {4, 29, 23, 25, 20, 36, 101, 15, inf, 35, 18};
    data_[9] = {31, 41, 27, 13, 16, 3, 99, 25, 35, inf, 38};
    data_[10] = {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, inf};
  }

  const double& operator()(int row, int columns) const {
    return data_[row][columns];
  }

  double& operator()(int row, int columns) { return data_[row][columns]; }

  std::vector<std::vector<double>>& GetData() { return data_; }

  const std::vector<std::vector<double>>& GetData() const { return data_; }

 private:
  const double inf = 1.0 / 0.0;
  std::vector<std::vector<double>> data_;
};

#endif  //  ADJ_MATRIX_H_