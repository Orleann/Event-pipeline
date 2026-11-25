cmake_minimum_required(VERSION 3.5)
project(Event-pipeline CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options( -Wall -Wextra -Wpedantic -Wconversion)

add_library(Event-pipeline_core
        src/main.cpp
        include/pipeline/event.h
        include/pipeline/thread_safe_queue.h
        include/pipeline/storage_strategy.h
        include/pipeline/BinaryFileStorage.h
)
target_include_directories(Event-pipeline_core PUBLIC include)

add_executable(Event-pipeline_server src/main.cpp
        include/pipeline/event.h
        include/pipeline/thread_safe_queue.h
        include/pipeline/storage_strategy.h
        include/pipeline/BinaryFileStorage.h
)
target_link_libraries(Event-pipeline_server PRIVATE Event-pipeline_core)
