cmake_minimum_required(VERSION 3.16)

project(sea_creature_projection_fun
  DESCRIPTION "important configuration in one window for KDE plasma"
  VERSION 0.1.0
  LANGUAGES CXX)

include_directories(${PROJECT_INCLUDE_DIR})

set(PIPE_EXAMPLE1_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pipe_example/main_simple_pipe.cpp
)

set(PIPE_EXAMPLE2_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pipe_example/main_fork_exec_pipe.cpp
)

add_executable(pipe_example1)
target_sources(pipe_example1
 PRIVATE
  ${PIPE_EXAMPLE1_SRC}
)

add_executable(pipe_example2)
target_sources(pipe_example2
 PRIVATE
  ${PIPE_EXAMPLE2_SRC}
)
