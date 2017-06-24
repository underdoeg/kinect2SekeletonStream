cmake_minimum_required(VERSION 2.8)

include(FindPkgConfig)

project(kinectStreamClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC "*.cpp" "*.h")
add_library(kinectStreamClient STATIC ${SRC})

pkg_check_modules(PKG REQUIRED libzmq)
target_include_directories(kinectStreamClient PRIVATE ${PKG_INCLUDE_DIRS})
target_include_directories(kinectStreamClient PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/../shared)
target_link_libraries(kinectStreamClient PRIVATE ${PKG_LIBRARIES} -pthread)
link_directories(${PKG_LIBRARY_DIRS})

