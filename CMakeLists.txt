cmake_minimum_required(VERSION 3.8)
project(jnp1_4)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS -DTEST_NUM=203)

set(SOURCE_FILES
        bakery.h
        cake.h
        pie.h)

add_executable(jnp1_4 ${SOURCE_FILES} tresc_zadania/bakery_example.cc)
add_executable(main tresc_zadania/main.cpp)
add_executable(Test ${SOURCE_FILES} bakery_test.cc)
#add_executable(bakeryTestCompilation private/bakeryTestCompilation.cpp bakery.h cake.h pie.h)