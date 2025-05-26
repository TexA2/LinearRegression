cmake_minimum_required(VERSION 3.8)
project(linearRegression)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -lminmea)
endif()


find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
  include
)

add_executable(linearRegression.out src/linear.cpp )
target_link_libraries(linearRegression.out glfw OpenGL::GL)



