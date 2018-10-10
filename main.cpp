#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <flann/flann.hpp>
//#include <flann/io/hdf5.h>

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

//  Vis3D<float> test;


  //printVecs(vecPts);
  return vecPts;
}

static unsigned int compileShader(unsigned int type,
                                  const std::string& source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int res;
  glGetShaderiv(id, GL_COMPILE_STATUS, &res);
  if (res == GL_FALSE){
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char* )alloca(length * sizeof (char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to Compile " <<
                 (type == GL_VERTEX_SHADER? "vertex" : "fragment" ) <<
                 std::endl << message << std::endl;
    glDeleteShader(id);
    return 0;
  }
  return id;
}

static unsigned int CreateShader(const std::string& vertexShader,
                        const std::string& fragmentshader)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentshader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

int main(int argc, char** argv)
{
  // generate some points
  int numPoints = 1000;
  int dim = 3;
  int maxRange = 100;
  generateRandomStdMat(numPoints,dim,maxRange);

  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
      return -1;



  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
      glfwTerminate();
      return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  std::cout << glGetString(GL_VERSION) << std::endl;

  if (glewInit() != GLEW_OK){
    std::cout << "GLEW INIT ERROR!" << std::endl;
  }

  float positions[6]={
    -0.5f,-0.5f,
     0.0f, 0.5f,
     0.5f,-0.5f,
  };
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof (float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                        sizeof (float) * 2, 0);


  std::string vertexShader =
      "#version 330 core\n"
      "layout(location=0) in vec4 position;\n"
      "\n"
      "void main() \n"
      "{\n"
      " gl_Position = position;\n"
      "}\n";

  std::string fragmentShader =
      "#version 330 core\n"
      "layout (location=0) out vec4 color;\n"
      "\n"
      "void main() \n"
      "{\n"
      " color = vec4(1.0, 0.0, 0.0, 1.0); \n"
      "}\n";
  unsigned int shader = CreateShader(vertexShader,fragmentShader);
  glUseProgram(shader);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);

      glDrawArrays(GL_TRIANGLES,0,3);

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
