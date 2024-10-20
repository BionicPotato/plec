cmake_minimum_required(VERSION 3.20)
project(plec-test)

enable_testing()

add_executable(basic basic.cpp)
target_link_libraries(basic plec-core)
add_test(NAME basic COMMAND $<TARGET_FILE:basic>)

