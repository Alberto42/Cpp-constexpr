cmake_minimum_required(VERSION 3.8)
project(jnp1_4)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        tresc_zadania/bakery_example.cc
        bakery.h
        cake.h
        pie.h)

add_executable(jnp1_4 ${SOURCE_FILES})
add_executable(main tresc_zadania/main.cpp)
#add_executable(bakeryTestCompilation private/bakeryTestCompilation.cpp bakery.h cake.h pie.h)