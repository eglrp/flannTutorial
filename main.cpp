#include <flann/flann.hpp>
#include <flann/io/hdf5.h>

#include <stdio.h>
#include <random>
#include "datatypes.h"
#include "visuallizer.hpp" 

void printVecs(stdMat& mat){
  for (Eigen::Vector3f& v: mat ){
    std::cout << v(0) << " " << v(1) << " " << v(2)  << std::endl;
  }
}

stdMat generateRandomStdMat(int numPoints, float maxRange ){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> randGen((-1)*maxRange,maxRange);
  stdMat vecPts;
  flann::Matrix<float> flannPts;
  for (int i = 0; i <numPoints; i++ )
  {
    Eigen::Vector3f temp;
    for (int j = 0; j < 3; j++){
      temp(j)=randGen(gen);
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
  int maxRange = 1;
  stdMat vecs = generateRandomStdMat(numPoints,maxRange);
  printVecs(vecs);

  Vis3D vis;

  // use the context in a separate rendering thread
  std::thread render_loop;
  render_loop = std::thread(vis, std::ref(vecs));
  render_loop.join();

  return 0;
}
