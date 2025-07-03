cmake_minimum_required(VERSION 3.10)
project(TextEditor)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/caesar)
include_directories(${PROJECT_SOURCE_DIR}/cpp)

add_library(caesar SHARED
        caesar/caesar_dll.c
        OPP/TextBuffer.h
        OPP/FileManager.h
        OPP/CryproManager.h
        OPP/DocumentManager.h
        OPP/ConfigManager.h
)

add_executable(notionSecondEdition
        main.c
        cpp/additionalFunctionallity.cpp
        caesar/CaesarCipher.cpp
        caesar/DataTypeHandler.cpp
        caesar/TextEditorEncryption.cpp
        OPP/HistoryManager.h
        OPP/TextEditor.h
)

target_link_libraries(notionSecondEdition caesar dl)