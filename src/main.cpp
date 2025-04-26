
#include <check_gl.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <system_error>
#include <type_traits>

constexpr int n = 120;
constexpr float pi = 3.1415926535897f;
constexpr float radius = 0.4f;
constexpr float inner_radius = 0.15f;

template <typename... Colors,
          typename = std::enable_if_t<
              std::conjunction_v<std::is_same<Colors, float>...> &&
              (sizeof...(Colors) == 3)>>
void render(int start, int end, float x, float y, Colors... colors) {
  glBegin(GL_TRIANGLES);
  for (int i = start; i < end; ++i) {
    int idx = i % n;

    float angle = idx / (float)n * pi * 2;
    float next_angle = (idx + 1) / (float)n * pi * 2;

    glColor3f(colors...);
    glVertex3f(radius * sinf(angle) + x, radius * cosf(angle) + y, 0.0f);
    glVertex3f(radius * sinf(next_angle) + x, radius * cosf(next_angle) + y,
               0.0f);
    glVertex3f(inner_radius * sinf(angle) + x, inner_radius * cosf(angle) + y,
               0.0f);

    glVertex3f(inner_radius * sinf(next_angle) + x,
               inner_radius * cosf(next_angle) + y, 0.0f);
    glVertex3f(inner_radius * sinf(angle) + x, inner_radius * cosf(angle) + y,
               0.0f);
    glVertex3f(radius * sinf(next_angle) + x, radius * cosf(next_angle) + y,
               0.0f);
  }
  CHECK_GL(glEnd());
}

int main() {
  if (!glfwInit()) {
    throw std::runtime_error("failed to initialize GLFW");
  }

  GLFWwindow *window = glfwCreateWindow(640, 640, "Example", NULL, NULL);

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

    float height = 0.5f;
    float bottom = height / 2;
    float width = sqrt(3.0f) / 2.0f * height;
    render(70, 170, 0.0f, height, 1.0f, 0.0f, 0.0f);
    render(10, 110, width, -bottom, 0.0f, 0.0f, 1.0f);
    render(30, 130, -width, -bottom, 0.0f, 1.0f, 0.0f);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
