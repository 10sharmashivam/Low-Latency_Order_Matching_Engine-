cmake_minimum_required(VERSION 3.16)
project(OrderMatchingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

find_package(yaml-cpp REQUIRED)

add_executable(order_engine
    src/main.cpp
    src/order_book/order.cpp
    src/order_book/order_book.cpp
    src/order_book/matching_engine.cpp
    src/networking/unix_socket.cpp
    src/utils/lock_free_queue.cpp
)

target_include_directories(order_engine PRIVATE include)
target_link_libraries(order_engine PRIVATE yaml-cpp pthread)