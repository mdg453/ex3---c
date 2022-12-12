cmake_minimum_required(VERSION 3.22)
project(ex3a_meitar453 C)
set(CMAKE_C_STANDARD 99)
add_compile_options("-Wpointer-arith" "-Werror")
include_directories(.)

add_executable(ex3a_meitar453
        linked_list.c
        linked_list.h
        tweets_generator.c
        markov_chain.c
        markov_chain.h)
