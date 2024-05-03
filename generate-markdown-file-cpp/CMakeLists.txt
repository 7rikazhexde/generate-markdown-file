cmake_minimum_required(VERSION 3.29.2)
project(generate_markdown_file)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source files
set(SOURCES
    src/main.cpp
    src/markdown_generator.cpp
    src/config.cpp
    src/file_processor.cpp
)

# Set header files
set(HEADERS
    src/markdown_generator.hpp
    src/config.hpp
    src/file_processor.hpp
)

# Set include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/toml11
)

# Specify external library (toml11)
#add_subdirectory(toml11)

# Generate executable file
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
#target_link_libraries(${PROJECT_NAME} toml11)

# Set install location
# include(GNUInstallDirs)
# install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})

## Specify full path
# install(TARGETS generate_markdown_file DESTINATION "$ENV{HOME}/develop/C/")

## Specify current directory
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_BINARY_DIR}/.. ABSOLUTE)
install(TARGETS generate_markdown_file DESTINATION "${PARENT_DIR}")
