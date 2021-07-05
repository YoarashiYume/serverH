cmake_minimum_required(VERSION 3.20.5)
project(server-h VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB server_h_SRC "*.h" "*.cpp")

add_executable(server-h ${server_h_SRC})

target_link_libraries(${PROJECT_NAME} Threads::Threads)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
