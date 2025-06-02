cmake_minimum_required(VERSION 3.10)
project(ByteOS C)

set(CMAKE_C_STANDARD 99)

# Adiciona o diretório utils como include path
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Adiciona os arquivos fonte
add_executable(ByteOS
    main.c
    utils/list.c
    utils/utils.c
)