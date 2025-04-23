cmake_minimum_required(VERSION 3.10)
project(kr-c-exercises)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Библиотека общего кода
file(GLOB_RECURSE LIB_SOURCES "src/lib/*.c")
add_library(common STATIC ${LIB_SOURCES})
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

# Упражнения с гарантированно уникальными именами
file(GLOB_RECURSE EXERCISES "src/exercises/*.c")

foreach(ex_src ${EXERCISES})
    # Генерируем уникальное имя из полного пути
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${ex_src})
    string(REPLACE "/" "__" rel_path ${rel_path})  # Двойное подчёркивание вместо /
    string(REGEX REPLACE "[ .]" "_" rel_path ${rel_path})
    string(REPLACE ".c" "" target_name ${rel_path})
    set(target_name "ex_${target_name}")

    add_executable(${target_name} ${ex_src})
    target_link_libraries(${target_name} common)
    message(STATUS "Added exercise: ${target_name}")
endforeach()
