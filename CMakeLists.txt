cmake_minimum_required(VERSION 3.10)
project(ByteOS C)

set(CMAKE_C_STANDARD 99)

# Adiciona o diretório utils como include path
# include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(
    src/kernel
    src/process
    src/utils
    src/disk
    src/memory
    src/printer
    src/semaphore
)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Adiciona os arquivos fonte
add_executable(ByteOS
    main.c
    src/utils/list.c
    src/utils/utils.c
    src/kernel/kernel.c
    src/process/process.c
    src/semaphore/semaph.c
    src/memory/memory.c
)

target_link_libraries(ByteOS m)
find_package(Threads REQUIRED)