#include <iostream>
#include "kt_regression.h"
#include "kt_data_io.h"
#include "kt_statistics.h"
#include "kt_matrix.h"
namespace kt = Kamaitachi;
int main()
{
  { //LinearRegressionTrainer single feature test
    kt::LinearRegressionTrainer reg;
    std::vector<float> y;
    kt::DataFile<float> file;
    file.Load("ex1data1.txt");
   
    std::vector<float> xj;
    xj = file.GetColumn(0);
    y = file.GetColumn(1);

    kt::DataMatrix featuresM;
    featuresM.AddColumn(0, 1, file.Rows());
    featuresM.AddColumn(1,xj);

    kt::DataVector yM(y);


    std::vector<float> testParams;
    testParams.push_back(0);
    testParams.push_back(0);
    float cost = kt::LinearRegressionTrainer::GetCost(testParams, featuresM, yM);
    std::cout << "Cost when theta = [0,0]: " << cost << " = 32.0727" << (kt::FloatUtils::Equals(32.0727,cost,0.01) ? " success" : " fail") << std::endl;
    testParams[0] = (-1);
    testParams[1] = (2);
    cost = kt::LinearRegressionTrainer::GetCost(testParams, featuresM, yM);
    std::cout << "Cost when theta = [-1,2]: " << cost << " = 54.2425" << (kt::FloatUtils::Equals(54.2425,cost,0.01) ? " success" : " fail") << std::endl;

    //reg.TrainWithGradientDescent(featuresM, yM, 1500, 0.0001);
    reg.TrainWithNormalEquation(featuresM, yM);

    std::cout << "Theta 0 = " << reg.GetParams()[0] << " = -3.63029" << (kt::FloatUtils::Equals(-3.63029,reg.GetParams()[0],0.01) ? " success" : " fail") << std::endl;
    std::cout << "Theta 1 = " << reg.GetParams()[1] << " = 1.16636" << (kt::FloatUtils::Equals(1.16636f, reg.GetParams()[1],0.01) ? " success" : " fail") << std::endl;

    cost = kt::LinearRegressionTrainer::GetCost(reg.GetParams(), featuresM, yM);
    std::cout << "Cost when theta = []: " << cost << " = 54.2425" << (kt::FloatUtils::Equals(54.2425, cost, 0.01) ? " success" : " fail") << std::endl;


  }
  std::cout << std::endl;
  std::cout << std::endl;
  { //LinearRegressionTrainer multiple feature test
    kt::LinearRegressionTrainer reg;
    std::vector<float> y;
    kt::DataFile<float> file;
    file.Load("ex1data2.txt");

    std::vector<float> xj;
    std::vector<float> xj2;

    xj = file.GetColumn(0);
    xj2 = file.GetColumn(1);

    y = file.GetColumn(2);

    kt::DataMatrix featuresM;
    featuresM.AddColumn(0, 1, file.Rows());
    featuresM.AddColumn(1, xj);
    featuresM.AddColumn(2, xj2);


    kt::DataVector yM(y);


    std::vector<float> testParams;
    testParams.push_back(0);
    testParams.push_back(0);
    testParams.push_back(0);

    float cost = kt::LinearRegressionTrainer::GetCost(testParams, featuresM, yM);
    std::cout << "Cost when theta = [0,0]: " << cost << " = 32.0727" << (kt::FloatUtils::Equals(32.0727, cost, 0.01) ? " success" : " fail") << std::endl;
    testParams[0] = (-1);
    testParams[1] = (2);
    testParams[2] = (0);

    cost = kt::LinearRegressionTrainer::GetCost(testParams, featuresM, yM);
    std::cout << "Cost when theta = [-1,2]: " << cost << " = 54.2425" << (kt::FloatUtils::Equals(54.2425, cost, 0.01) ? " success" : " fail") << std::endl;

    //reg.TrainWithGradientDescent(featuresM, yM, 450, 0.01);
    reg.TrainWithNormalEquation(featuresM, yM);

    std::cout << "Theta 0 = " << reg.GetParams()[0] << " = -3.63029" << (kt::FloatUtils::Equals(-3.63029, reg.GetParams()[0], 0.01) ? " success" : " fail") << std::endl;
    std::cout << "Theta 1 = " << reg.GetParams()[1] << " = 1.16636" << (kt::FloatUtils::Equals(1.16636f, reg.GetParams()[1], 0.01) ? " success" : " fail") << std::endl;

    cost = kt::LinearRegressionTrainer::GetCost(reg.GetParams(), featuresM, yM);
    std::cout << "Cost when theta = []: " << cost << " = 54.2425" << (kt::FloatUtils::Equals(54.2425, cost, 0.01) ? " success" : " fail") << std::endl;


    
  }

}
