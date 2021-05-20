cmake_minimum_required(VERSION 3.10)

project(MAT)

find_package(OpenCV REQUIRED)

include_directories(
  #external_libs/include
  ${PROJECT_SOURCE_DIR}/data
  ${OpenCV_INCLUDE_DIRS}
)

include(CTest)
enable_testing()

add_subdirectory(src)
