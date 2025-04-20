
#include <check_gl.hpp>
#include <cstdlib>
#include <iostream>
#include <system_error>

int main() {
  if (!glfwInit()) {
    throw std::runtime_error("failed to initialize GLFW");
  }

  GLFWwindow *window = glfwCreateWindow(1024, 768, "Example", NULL, NULL);

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("GLFW failed to create window");
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::runtime_error("GLAD failed to load GL functions");
  }

  printf("OpenGL version: %s", glGetString(GL_VERSION));

  glfwSwapInterval(1);

  CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));
  CHECK_GL(glEnable(GL_POINT_SMOOTH));
  CHECK_GL(glEnable(GL_BLEND));
  CHECK_GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  CHECK_GL(glPointSize(64.0f));

  while (!glfwWindowShouldClose(window)) {

    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    CHECK_GL(glEnd());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
