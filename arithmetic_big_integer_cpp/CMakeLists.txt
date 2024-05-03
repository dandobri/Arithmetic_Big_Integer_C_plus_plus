cmake_minimum_required(VERSION 3.26)
project(backlog_itmo_cpp_ln_dandobri_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(backlog_itmo_cpp_ln_dandobri_main
        LN.cpp
        LN.h
        main.cpp
        return_codes.h
        vector.cpp
        vector.h
        exceptionsLN.h)
