
# Cmake Project settings
# --------------------------------------------------------------------

project(quarkwindow)

cmake_minimum_required(VERSION 3.0)

# Build GLFW
# --------------------------------------------------------------------
set(OpenGL_GL_PREFERENCE LEGACY)
if (WIN32)
  set(glfw_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/glfw)
  include_directories(${glfw_dir}/include)
  add_subdirectory(${glfw_dir})
else()
  find_package(glfw3 REQUIRED)
endif()
include_directories(.)


# Final CMake rules for project
# --------------------------------------------------------------------
add_subdirectory(src/quarkWindow)
