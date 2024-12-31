cmake_minimum_required(VERSION 3.20)
project(plec-test)

enable_testing()

function(test name)
    add_executable(${name} ${name}.cpp test.cpp)
    target_link_libraries(${name} optimized plec-core debug plec-core.db)
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endfunction()

test(basic)
test(getnextstatement)
test(parsedecl)
test(regress-23)
test(targets)

set(files
    getnextstatement.ple
    regress-23.ple
    targets0.ple
    targets1.ple
    targets2.ple
)
set(targets
    getnextstatement
    regress-23
    targets
    targets
    targets
)

foreach(file target IN ZIP_LISTS files targets)
    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/${file}
                ${CMAKE_CURRENT_BINARY_DIR}/${file}
    )
endforeach()

