cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(philo_bonus VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(philo_bonus
    src/cul_str.c
    src/gastr_act.c
    src/philo_b.c
    src/tbl_gov.c
    src/tbl_serv.c
)

# Include directories
target_include_directories(philo_bonus PRIVATE inc)

# Link libraries
target_link_libraries(philo_bonus pthread)
