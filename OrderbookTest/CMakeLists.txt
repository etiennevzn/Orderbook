cmake_minimum_required(VERSION 3.12) # version can be different

set(GOOGLETEST_VERSION 1.15.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

project(OrderbookTest) 

enable_testing() 
add_subdirectory(googletest) 
include_directories(googletest/include) 

add_executable(mytests mytests.cpp) 
target_link_libraries(mytests PRIVATE gtest) 

include(GoogleTest)
gtest_discover_tests(mytests) 