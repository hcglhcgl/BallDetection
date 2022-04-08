project(ballFinder)
cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(ballFinder main.cpp balls.cpp)

#target_link_libraries(ballFinder imutils_cpp ${OpenCV_LIBS} curl)
target_link_libraries(ballFinder ${OpenCV_LIBS} )