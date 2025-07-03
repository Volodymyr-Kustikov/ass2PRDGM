cmake_minimum_required(VERSION 3.10)
project(TextEditor)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/caesar)
include_directories(${PROJECT_SOURCE_DIR}/cpp)

add_library(caesar SHARED
        caesar/caesar_dll.c
)

add_executable(notionSecondEdition
        main.c
        cpp/additionalFunctionallity.cpp
        caesar/CaesarCipher.cpp
        caesar/DataTypeHandler.cpp
        caesar/TextEditorEncryption.cpp
)

target_link_libraries(notionSecondEdition caesar dl)