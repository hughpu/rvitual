
#include <check_gl.h>
#include <cstdlib>
#include <iostream>
#include <system_error>

int main() {
  if (!glfwInit()) {
    throw std::runtime_error("failed to initialize GLFW");
  }

  GLFWwindow *window = glfwCreateWindow(640, 480, "Example", NULL, NULL);

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("GLFW failed to create window");
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGL()) {
    glfwTerminate();
    throw std::runtime_error("GLAD failed to load GL functions");
  }

  printf("OpenGL version: %s", glGetString(GL_VERSION));

  while (!glfwWindowShouldClose(window)) {

    glEnable(GL_POINT_SMOOTH);
    glPointSize(64.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
