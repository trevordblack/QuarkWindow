# --------------------------------------------------------------------
# Cmake Project settings
# -------------------------------------------------------------------
project(quarkwindow)

cmake_minimum_required(VERSION 3.0)

# -------------------------------------------------------------------
# Build GLFW
# --------------------------------------------------------------------
set(OpenGL_GL_PREFERENCE LEGACY)
if (WIN32)
  set(glfw_dir ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
  include_directories(${glfw_dir}/include)
  add_subdirectory(${glfw_dir})
else()
  find_package(glfw3 REQUIRED)
endif()

# -------------------------------------------------------------------
# Build QuarkWindow
# --------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_library(quarkWindow
  quarkWindow.h
  quarkWindow.cpp
)

# -------------------------------------------------------------------
# Final CMake rules for project
# --------------------------------------------------------------------
find_package(OpenGL REQUIRED)

add_executable(helloWindow
  exampleWindow.cpp
)

target_link_libraries(helloWindow
  quarkWindow
  glfw
  ${OPENGL_gl_LIBRARY}
)

