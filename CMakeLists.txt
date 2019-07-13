cmake_minimum_required(VERSION 3.1)
project(fluidsim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# File Gathering
file(GLOB_RECURSE HDRS
	${SRC_DIR}/*.h
	${SRC_DIR}/*.hpp
)
file(GLOB_RECURSE SRCS
	${SRC_DIR}/*.cpp
	${SRC_DIR}/*.c
)

add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})

# Use Modern OpenGL 3.0
set(OpenGL_GL_PREFERENCE "GLVND")
include(FindPkgConfig)


pkg_search_module(SDL2 REQUIRED sdl2)

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 not found!")
endif(NOT SDL2_FOUND)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
	message(FATAL_ERROR "GLEW not found!")
endif(NOT GLEW_FOUND)

# Define the include DIRs
include_directories(
	${fluidsim_SOURCE_DIR}/src
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries( fluidsim
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
)

# So we can use res/ folder from build dir.
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${fluidsim_SOURCE_DIR}/res ${fluidsim_BINARY_DIR}/res RESULT_VARIABLE exitcode)
