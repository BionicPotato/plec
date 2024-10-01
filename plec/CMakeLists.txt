cmake_minimum_required(VERSION 3.20)
project(plec)

add_executable(plec plec.cpp)

install(TARGETS plec DESTINATION bin)
target_link_libraries(plec optimized plec-core debug plec-core.db)
