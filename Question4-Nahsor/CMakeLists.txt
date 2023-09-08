cmake_minimum_required(VERSION 3.8)

project(nahsor)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} "./include")

set(SOURCE_FILES src/nahsor_main.cpp src/nahsor_detector.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})