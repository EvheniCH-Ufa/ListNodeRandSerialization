cmake_minimum_required(VERSION 3.5)

project(ListNodeRandSerialization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    ListNodeRandSerialization
    ListNodeSerializator.h
    ListNodeSerializator.CPP
    main.cpp
    )
