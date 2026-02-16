cmake_minimum_required(VERSION 3.10)
project(hf_tokenizers_cpp)

set(CMAKE_CXX_STANDARD 23)

# Define paths for the Rust library
set(TOKENIZER_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tokenizers/tokenizers/target/release")
set(TOKENIZER_LIB_PATH "${TOKENIZER_LIB_DIR}/libtokenizers.so")

# Custom command to build the Rust library using Cargo
add_custom_command(
    OUTPUT ${TOKENIZER_LIB_PATH}
    COMMAND git submodule sync
    COMMAND git submodule update --init --recursive
    COMMAND cargo build --release
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tokenizers/tokenizers"
    COMMENT "Synchronizing submodules and building Rust tokenizers library..."
    VERBATIM
)

# Custom target that depends on the library file
add_custom_target(build_rust_tokenizers DEPENDS ${TOKENIZER_LIB_PATH})

# Main executable
add_executable(hf_tokenizers_cpp main.cpp)

# Ensure the Rust library is built before the C++ executable
add_dependencies(hf_tokenizers_cpp build_rust_tokenizers)

# Link the .so file and required system libraries
target_link_libraries(hf_tokenizers_cpp PRIVATE 
    ${TOKENIZER_LIB_PATH}
    pthread
    dl
    m
)

# Add include directories (tokenizers.h is in the root)
target_include_directories(hf_tokenizers_cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
