#ifndef ADJ_MATRIX_H_
#define ADJ_MATRIX_H_

#include <vector>

class AdjMatrix {
 public:
  AdjMatrix() = default;

  void Init(int size) {
    data_.reserve(size * size);
    offset_ = size;
  }

  void InitWithNumber(int size, double num) {
    data_.resize(size * size, num);
    offset_ = size;
  }

  void Push(double num) { data_.push_back(num); }

  void Clear() { data_.clear(); }

  double& operator()(int row, int columns) {
    return data_[row * offset_ + columns];
  }

  const double& operator()(int row, int columns) const {
    return data_[row * offset_ + columns];
  }

  std::vector<double>& GetData() { return data_; }

  const std::vector<double>& GetData() const { return data_; }

 private:
  int offset_ = 0;
  std::vector<double> data_;
};

#endif  //  ADJ_MATRIX_H_