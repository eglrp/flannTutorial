#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <flann/flann.hpp>
//#include <flann/io/hdf5.h>

#include "datatypes.h"
#include <random>
#include <chrono>
#include <thread>
#include <condition_variable>


class Process
{
private:
  stdMat m_2Vis;

  void printVecs(stdMat& mat){
    for (Eigen::Vector3f& v: mat ){
      std::cout << v(0) << " " << v(1) << " " << v(2)  << std::endl;
    }
  }

  void generateRandomStdMat(int numPoints, float maxRange ){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> randGen((-1)*maxRange,maxRange);
    //stdMat vecPts;
    m_2Vis.clear();
    flann::Matrix<float> flannPts;
    for (int i = 0; i <numPoints; i++ )
    {
      Eigen::Vector3f temp;
      for (int j = 0; j < 3; j++){
        temp(j)=randGen(gen);
      }
      //vecPts.push_back(temp);
      m_2Vis.push_back(temp);
    }
    //printVecs(vecPts);
    //return vecPts;
  }

public:
  Process(){}

//  stdMat& operator()(){
//    return m_2Vis;
//  }

  stdMat& data(){
    return m_2Vis;
  }

  void process(std::condition_variable& convar){
    // generate some points
    int numPoints = 1000;
    int maxRange = 1;
    bool continue_running = true;
    std::mutex alwaysLockedMutex;
    std::unique_lock<std::mutex> lck(alwaysLockedMutex);

    while(continue_running){
      generateRandomStdMat(numPoints,maxRange);
      //printVecs(m_2Vis);
      std::cv_status convar_status = convar.wait_for(lck, std::chrono::seconds(1));
      if (convar_status == std::cv_status::no_timeout)
        continue_running = false;
    }
  }
};

#endif // PROCESS_HPP
