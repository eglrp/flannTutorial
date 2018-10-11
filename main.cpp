#include <flann/flann.hpp>
#include <flann/io/hdf5.h>

#include <stdio.h>
#include <random>


typedef std::vector<std::vector<float>> stdMat;

void printVecs(stdMat& mat){
  for (std::vector<float>& v: mat ){
    for (float &f : v){
      std::cout << f << " ";
    }
    std::cout << std::endl;
  }
}

stdMat generateRandomStdMat(int numPoints, int dim, float maxRange){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> randGen((-1)*maxRange,maxRange);
  stdMat vecPts;
  flann::Matrix<float> flannPts;
  for (int i = 0; i <numPoints; i++ )
  {
    std::vector<float> temp;
    for (int j = 0; j < dim; j++){
      temp.push_back(randGen(gen));
    }
    vecPts.push_back(temp);
  }
  //printVecs(vecPts);
  return vecPts;
}

int main(int argc, char** argv)
{
  // generate some points
  int numPoints = 1000;
  int dim = 3;
  int maxRange = 100;
  generateRandomStdMat(numPoints,dim,maxRange);

  return 0;
}
