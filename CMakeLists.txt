cmake_minimum_required(VERSION 3.23)
project(lab2)
project(lab1)

set(CMAKE_CXX_STANDARD 23)
set(RAY_CODE_DIR "/home/shriller44/university/University/AdvancedComputerGraphics-CM30075/coursework/labs/raySourceCode/coursework-starter")

find_package(fmt)

file(GLOB raySources "${RAY_CODE_DIR}/*.cpp")

link_libraries(fmt::fmt)
#add_executable(lab1 main_lab1.cpp ${raySources})
#add_executable(lab2 main_lab2.cpp ${raySources})
add_executable(lab3 main_lab34.cpp ${raySources})

include_directories("${RAY_CODE_DIR}")
