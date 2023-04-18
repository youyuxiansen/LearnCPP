cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "/home/yousixia/util_projects/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "/home/yousixia/util_projects/vcpkg/installed/x64-windows")
project(test_engine)

set(CMAKE_CXX_STANDARD 11)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
message("OpenCV_DIR is ${OpenCV_DIR}")
message("OpenCV_INCLUDE_DIRS is ${OpenCV_INCLUDE_DIRS}")
message("Eigen3_DIR is ${Eigen3_DIR}")
message("EIGEN3_INCLUDE_DIR is ${EIGEN3_INCLUDE_DIR}")

include_directories(./)
add_executable(test_engine test_calc_can_clean_area.cpp)

# Additional Dependencies
target_link_libraries(test_engine ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})