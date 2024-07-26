cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OpenCV_DIR "C:/lib/install/opencv/x64/vc17/lib")

project(camera_port)

find_package(OpenCV REQUIRED)

add_executable(camera_port camera_port.cpp)

target_link_libraries(camera_port ${OpenCV_LIBS})

target_include_directories(camera_port PRIVATE ${OpenCV_INCLUDE_DIRS})
