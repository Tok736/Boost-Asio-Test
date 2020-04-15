cmake_minimum_required(VERSION 3.9)
set(PROJECT_NAME Boost-Asio-Test)
project(${PROJECT_NAME} CXX)

SET(GCC_COVERAGE_COMPILE_FLAGS "-lboost_system -lboost_thread")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "-lm -Wno-unknown-pragmas -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage -lgcov")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov --coverage")

include_directories(include)

file(GLOB_RECURSE SOURCE "src/*.cpp")
add_executable(${PROJECT_NAME} main.cpp ${SOURCE})

# ==== Need for debugging tests ==== #
#file(GLOB_RECURSE TEST_CPPS "test/*/*.cpp")
#add_executable(${PROJECT_NAME} ${SOURCE} ${TEST_CPPS} test/test.cpp)

target_link_libraries(${PROJECT_NAME} m)

# ==== Linking with Boost ==== #
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED COMPONENTS system filesystem date_time regex thread)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
