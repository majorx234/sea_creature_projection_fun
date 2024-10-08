cmake_minimum_required(VERSION 3.16)

project(sea_creature_projection_fun
  DESCRIPTION "animate self painted images of water animals"
  VERSION 0.1.0
  LANGUAGES CXX)

set( PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )
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
set(RAYLIB_EXAMPLE3_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raylib_examples/main_render_pipeline.cpp
)
set(RAYLIB_EXAMPLE4_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raylib_examples/main_render_pipeline_moving_figures.cpp
)
set(RAYLIB_EXAMPLE5_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raylib_examples/main_render_pipeline_moving_figures_scaling.cpp
)
set(CREATE_TEXTURE_ANIMATION_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/create_texture_animation/create_simple_texture_map.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/stb/
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

add_executable(raylib_example3)
target_sources(raylib_example3
 PRIVATE
  ${RAYLIB_EXAMPLE3_SRC}
)
target_include_directories(raylib_example3
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)
target_link_libraries(raylib_example3
  ${raylib_LIBRARIES}
)

add_executable(raylib_example4)
target_sources(raylib_example4
 PRIVATE
  ${RAYLIB_EXAMPLE4_SRC}
)
target_include_directories(raylib_example4
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)
target_link_libraries(raylib_example4
  ${raylib_LIBRARIES}
)

add_executable(raylib_example5)
target_sources(raylib_example5
 PRIVATE
  ${RAYLIB_EXAMPLE5_SRC}
)
target_include_directories(raylib_example5
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)
target_link_libraries(raylib_example5
  ${raylib_LIBRARIES}
)

add_executable(create_texture_animation)
target_sources(create_texture_animation
 PRIVATE
  ${CREATE_TEXTURE_ANIMATION_SRC}
)
target_include_directories(create_texture_animation
 PRIVATE
  ${PROJECT_INCLUDE_DIR}/stb
)
target_compile_definitions(create_texture_animation
 PUBLIC
 STB_IMAGE_IMPLEMENTATION
 STB_IMAGE_WRITE_IMPLEMENTATION
)
#target_link_libraries(create_texture_animation
## no libs yet
#)

