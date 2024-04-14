cmake_minimum_required(VERSION 3.16)

project(sea_creature_projection_fun
  DESCRIPTION "important configuration in one window for KDE plasma"
  VERSION 0.1.0
  LANGUAGES CXX)

include_directories(${PROJECT_INCLUDE_DIR})

find_package(raylib)

set(PIPE_EXAMPLE1_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pipe_example/main_simple_pipe.cpp
)

set(PIPE_EXAMPLE2_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pipe_example/main_fork_exec_pipe.cpp
)

set(RAYLIB_EXAMPLE1_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raylib_examples/main_textures_bouncing.cpp
)

set(RAYLIB_EXAMPLE2_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raylib_examples/main_figures_bouncing.cpp
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

add_executable(raylib_example1)
target_sources(raylib_example1
 PRIVATE
  ${RAYLIB_EXAMPLE1_SRC}
)
target_include_directories(raylib_example1
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)
target_link_libraries(raylib_example1
  ${raylib_LIBRARIES}
)

add_executable(raylib_example2)
target_sources(raylib_example2
 PRIVATE
  ${RAYLIB_EXAMPLE2_SRC}
)
target_include_directories(raylib_example2
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)
target_link_libraries(raylib_example2
  ${raylib_LIBRARIES}
)

