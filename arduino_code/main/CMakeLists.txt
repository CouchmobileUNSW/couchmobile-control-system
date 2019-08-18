

cmake_minimum_required(VERSION 2.8.11)

# Project name
project(control)

# This setting is useful for providing JSON file used by CodeLite for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set default locations
set(CL_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/motor_control_2/cmake-build-Debug/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})

set(CONFIGURATION_NAME "Debug")

# Projects


# Top project
# Define some variables
set(PROJECT_control_PATH "${CMAKE_CURRENT_LIST_DIR}")
set(WORKSPACE_PATH "${CMAKE_CURRENT_LIST_DIR}/motor_control_2")



#{{{{ User Code 1
# Place your code here
#}}}}

include_directories(
    .
    .
    D:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/
)


# Compiler options
add_definitions(-g)
add_definitions(-O0)
add_definitions(-Wall)

# Linker options


if(WIN32)
    # Resource options
endif(WIN32)

# Library path
link_directories(
    .
)

# Define the CXX sources
set ( CXX_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/src/testFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/RingBuffer.h
)

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0 -Wall")

if(WIN32)
    enable_language(RC)
    set(CMAKE_RC_COMPILE_OBJECT
        "<CMAKE_RC_COMPILER> ${RC_OPTIONS} -O coff -i <SOURCE> -o <OBJECT>")
endif(WIN32)



#{{{{ User Code 2
# Place your code here
#}}}}

add_executable(control ${RC_SRCS} ${CXX_SRCS} ${C_SRCS})
target_link_libraries(control ${LINK_OPTIONS})



#{{{{ User Code 3
# Place your code here
#}}}}

