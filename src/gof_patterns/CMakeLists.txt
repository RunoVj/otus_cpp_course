cmake_minimum_required(VERSION 3.5)

add_library(gof_patterns INTERFACE
        observer/observer.h
        mediator/mediator.h)

target_include_directories(gof_patterns INTERFACE .)
