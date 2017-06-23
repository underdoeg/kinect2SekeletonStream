cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../client ${CMAKE_CURRENT_BINARY_DIR}/client)

project(sampleClient)
add_executable(${PROJECT_NAME} "main.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../client)
target_link_libraries(sampleClient PRIVATE kinectStreamClient)
