cmake_minimum_required(VERSION 3.27)

project(Rosetta C)

set(CMAKE_C_STANDARD 99)

# Adicione os arquivos de origem ao seu projeto
add_executable(Rosetta CPU/6502/make.c
        CPU/6502/cpu6502.c
        CPU/6502/mem6502/mem6502.c
)

# Encontre todos os arquivos .h nos subdiretórios de "include" e "other_include_directory"
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/CPU/6502/Instructions/*.h
)

# Extraia os diretórios dos arquivos .h
foreach(HEADER_FILE ${HEADER_FILES})
    get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
    list(APPEND HEADER_DIRS ${HEADER_DIR})
endforeach()

## Remova diretórios duplicados
#list(REMOVE_DUPLICATES HEADER_DIRS)

# Adicione os diretórios de inclusão ao alvo Rosetta
target_include_directories(Rosetta
        PRIVATE
        ${HEADER_DIRS}
)
