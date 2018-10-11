#include <flann/flann.hpp>
#include <flann/io/hdf5.h>

#include <stdio.h>
#include <random>

#include <pangolin/pangolin.h>

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
  stdMat vecs = generateRandomStdMat(numPoints,dim,maxRange);
  printVecs(vecs);

  pangolin::CreateWindowAndBind("Main",640,480);
  glEnable(GL_DEPTH_TEST);

  // Define Projection and initial ModelView matrix

  pangolin::OpenGlRenderState s_cam(
		  pangolin::ProjectionMatrix(640,480,420,420,320,240,0.2,100),
		  pangolin::ModelViewLookAt(-2,2,-2, 0,0,0, pangolin::AxisY)
		  );

 // Create Interactive View in window
 
  pangolin::Handler3D handler(s_cam);
  pangolin::View& d_cam = pangolin::CreateDisplay()
	  .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
	  .SetHandler(&handler);

  while( !pangolin::ShouldQuit() )
  {
    // Clear screen and activate view to render into
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d_cam.Activate(s_cam);

    // Render OpenGL Cube
    pangolin::glDrawColouredCube();

    // Swap frames and Process Events
    pangolin::FinishFrame();
  }
  return 0;
}
