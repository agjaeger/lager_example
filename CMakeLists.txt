cmake_minimum_required(VERSION 3.10)

# set the project name
project(
    lagerexample
    VERSION 1.0.0
)

# add the executable
add_executable(
    ${PROJECT_NAME}
    source/main.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC "${PROJECT_BINARY_DIR}"
    PUBLIC include/
    PUBLIC external/
)
