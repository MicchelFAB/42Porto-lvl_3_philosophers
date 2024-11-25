cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(philo VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(philo
    src/init.c
    src/mini_ft.c
    src/philosophers.c
    src/utils.c
)

# Include directories
target_include_directories(philo PRIVATE inc)

# Link libraries
target_link_libraries(philo pthread)
