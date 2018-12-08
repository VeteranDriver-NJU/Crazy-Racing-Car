cmake_minimum_required(VERSION 3.8.2)
project(spinning_car)

set(CMAKE_CXX_STANDARD 11)

add_executable(spinning_car main.cpp Util.h Camera.h)
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})