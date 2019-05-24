#include <iostream>
#include "kt_regression.h"
#include "kt_data_io.h"
namespace kt = Kamaitachi;
int main()
{
  kt::LinearRegressionTrainer reg;
  std::vector<std::vector<float>> x;
  std::vector<float> y;
  kt::DataFile<float> file;
  file.Load("ex1data1.txt");

  std::vector<float> xj;
  xj = file.GetColumn(0);
  y = file.GetColumn(1);

  x.resize(xj.size());
  for (size_t i = 0; i < x.size(); i++)
  {
    x[i].resize(2);
    x[i][0] = 1;
    x[i][1] = xj[i];
  }
  reg.Train(x, y, 1500, 0.01);
}
