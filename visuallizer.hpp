#ifndef VISUALLIZER_HPP
#define VISUALLIZER_HPP

#include "pangolin/pangolin.h"
#include <thread>
#include "datatypes.h"
#include <condition_variable>

static const std::string window_name = "HelloPangolinThreads";

//template<typename T>
class Vis3D{
private:
  void setup() {
      // create a window and bind its context to the main thread
      pangolin::CreateWindowAndBind(window_name, 640, 480);

      // enable depth
      glEnable(GL_DEPTH_TEST);

      // unset the current context from the main thread
      pangolin::GetBoundWindow()->RemoveCurrent();
  }

  void run(const stdMat &pts,  std::condition_variable& conv) {
    // fetch the context and bind it to this thread
    pangolin::BindToContext(window_name);

    // we manually need to restore the properties of the context
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

    std::cout << "last element of vector: " << pts.back()(2) << std::endl;
    while( !pangolin::ShouldQuit() )
    {
      // Clear screen and activate view to render into
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      d_cam.Activate(s_cam);

      // Render OpenGL Cube
      //pangolin::glDrawColouredCube();
      pangolin::glDrawPoints(pts);

      // Swap frames and Process Events
      pangolin::FinishFrame();
    }

    conv.notify_all();

    // unset the current context from the main thread
    pangolin::GetBoundWindow()->RemoveCurrent();
  }

public:
  Vis3D(){
    setup();
  }

  void operator()(const stdMat &pts, std::condition_variable& conv){
    run(pts,conv);
  }

  void plotPoints(std::vector<std::vector<float>>& mat){
  }
};

#endif // VISUALLIZER_HPP
