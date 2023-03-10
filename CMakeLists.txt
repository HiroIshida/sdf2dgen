cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS_INIT} -Wall -fPIC")

find_package(Eigen3 REQUIRED)
ADD_DEFINITIONS(-DEIGEN_NO_DEBUG)
include_directories(${EIGEN3_INCLUDE_DIR} cpp)

add_library(sdf2d STATIC cpp/sdf.cpp)

add_executable(demo example/demo.cpp)
target_link_libraries(demo sdf2d)

find_package(GTest REQUIRED)
add_executable(test_sdf cpp/test.cpp)
target_include_directories(test_sdf PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_sdf ${GTEST_LIBRARIES} pthread sdf2d)

add_subdirectory(pybind11)
pybind11_add_module(_pysdf2d cpp/wrapper.cpp)
target_link_libraries(_pysdf2d PRIVATE sdf2d)
install(TARGETS _pysdf2d DESTINATION .)
