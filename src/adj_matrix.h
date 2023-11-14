#ifndef ADJ_MATRIX_H_
#define ADJ_MATRIX_H_

#include <vector>

class AdjMatrix {
 public:
  AdjMatrix() = default;

  void init(int size) { data_.resize(size); }

  void Push(double num) { data_.push_back(num); }

  void SetJump(int num) { jump_ = num; }

  double& operator()(int row, int columns) {
    return data_[row * jump_ + columns];
  }

  const double& operator()(int row, int columns) const {
    return data_[row * jump_ + columns];
  }

  void SetData(std::vector<double> data) { data_ = data; }

  std::vector<double>& GetData() { return data_; }

  const std::vector<double>& GetData() const { return data_; }

 private:
  int jump_ = 0;
  std::vector<double> data_;
};

#endif  //  ADJ_MATRIX_H_