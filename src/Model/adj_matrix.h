#ifndef ADJ_MATRIX_H_
#define ADJ_MATRIX_H_

#include <cmath>
#include <iostream>
#include <vector>

class AdjMatrix {
 public:
  AdjMatrix() = default;

  void Init(int size);

  void InitWithNumber(int size, double num);

  void Push(double num);

  void Print();

  void Clear();

  double& operator()(int row, int columns);

  const double& operator()(int row, int columns) const;

  std::vector<double>& GetData();

  const std::vector<double>& GetData() const;

 private:
  int offset_ = 0;
  std::vector<double> data_;
};

#endif  //  ADJ_MATRIX_H_