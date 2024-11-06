# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project information
project(YourProject LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCE_FILES 1.cpp 2.cpp 3.cpp 4.cpp 5.cpp)

# Loop through each source file to create executables
foreach(source_file IN LISTS SOURCE_FILES)
    # Extract file name without extension to use as target name
    get_filename_component(target_name ${source_file} NAME_WE)

    # Define executable target for each source file
    add_executable(${target_name} ${source_file})

    # Set output directory for each executable
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${target_name}"
    )
endforeach()

# Add a custom target to build all executables without specific dependencies
add_custom_target(all_targets
    COMMENT "Building all executables"
)

# Add a custom target to clean all executables, ensuring compatibility across platforms
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/bin"
    COMMENT "Cleaning all generated executables"
)
