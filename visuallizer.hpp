#ifndef VISUALLIZER_HPP
#define VISUALLIZER_HPP

#include "pangolin/pangolin.h"

template<typename T>
class Vis3D{
private:

public:
  Vis3D(){
    pangolin::CreateWindowAndBind("Main",640,480);
		glEnable(GL_DEPTH_TEST);

		pangolin::OpenGlRenderState s_cam(
										pangolin::ProjectionMatrix(640,480,420,420,320,240,0.2,100),
										pangolin::ModelViewLookAt(-2,2,-2,0,0,0, pangolin::AxisY)
										);

		// Create Interactive View in window 
		pangolin::Handler3D handler(s_cam);
  }

  void plotPoints(std::vector<std::vector<float>>& mat){

  }
};

#endif // VISUALLIZER_HPP
