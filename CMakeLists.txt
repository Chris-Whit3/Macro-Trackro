cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

project(macrotrackro)
set(SRC src/main.cpp src/get_nutrition_facts.cpp src/engine.cpp src/Product.cpp src/User.cpp)

add_executable(combined ${SRC})

find_package(OpenCV REQUIRED)

target_link_libraries(combined PRIVATE ZXing curl ${OpenCV_LIBS})

target_include_directories(combined PRIVATE include ${OpenCV_INCLUDE_DIRS}) 

