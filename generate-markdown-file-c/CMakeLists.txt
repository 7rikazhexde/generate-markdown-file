cmake_minimum_required(VERSION 3.29.2)
project(generate-markdown-file C)

# Set source files
set(SOURCE_FILES
    src/main.c
    src/process_file.c
    src/process_directory.c
    src/utils.c
    tomlc99/toml.c
)

# Set header files
set(HEADER_FILES
    src/process_file.h
    src/process_directory.h
    src/utils.h
    tomlc99/toml.h
)

# Set include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tomlc99
)

# Generate executable file
add_executable(generate_markdown_file ${SOURCE_FILES} ${HEADER_FILES})

# Set install location
## Specify full path
#install(TARGETS generate_markdown_file DESTINATION "$ENV{HOME}/develop/C/")

## Specify current directory
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_BINARY_DIR}/.. ABSOLUTE)
install(TARGETS generate_markdown_file DESTINATION "${PARENT_DIR}")