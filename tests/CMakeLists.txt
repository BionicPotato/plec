cmake_minimum_required(VERSION 3.20)
project(plec-test)

enable_testing()

add_executable(basic basic.cpp test.cpp)
target_link_libraries(basic optimized plec-core debug plec-core.db)
add_test(NAME basic COMMAND $<TARGET_FILE:basic>)

add_executable(getnextstatement getnextstatement.cpp test.cpp)
target_link_libraries(getnextstatement optimized plec-core debug plec-core.db)
# Copy getnextstatement.ple to binary dir
add_custom_command(
    TARGET getnextstatement POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/getnextstatement.ple
            ${CMAKE_CURRENT_BINARY_DIR}/getnextstatement.ple
)
add_test(NAME getnextstatement COMMAND $<TARGET_FILE:getnextstatement>)

add_executable(parsedecl parsedecl.cpp test.cpp)
target_link_libraries(parsedecl optimized plec-core debug plec-core.db)
add_test(NAME parsedecl COMMAND $<TARGET_FILE:parsedecl>)

add_executable(regress-23 regress-23.cpp test.cpp)
target_link_libraries(regress-23 optimized plec-core debug plec-core.db)
# Copy regress-23.ple to binary dir
add_custom_command(
    TARGET regress-23 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/regress-23.ple
            ${CMAKE_CURRENT_BINARY_DIR}/regress-23.ple
)
add_test(NAME regress-23 COMMAND $<TARGET_FILE:regress-23>)

