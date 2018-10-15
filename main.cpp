#include "process.hpp"
#include <stdio.h>
#include "datatypes.h"
#include "visuallizer.hpp" 


int main()//int argc, char** argv
{
  Vis3D vis;
  Process pr;
  std::condition_variable endCond;

  // use the context in a separate rendering thread
  std::thread render_loop;
  render_loop = std::thread(vis, std::ref(pr.data()), std::ref(endCond));
  pr.process(endCond);
  render_loop.join();
  return 0;
}
