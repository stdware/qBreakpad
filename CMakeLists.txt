cmake_minimum_required(VERSION 3.17)

project(qBreakpad VERSION 0.2.1.1 LANGUAGES CXX)

option(QBREAKPAD_BUILD_STATIC "Build static library" off)
option(QBREAKPAD_BUILD_SHARED "Build shared library" off)
option(QBREAKPAD_INSTALL "Install library" on)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(QBREAKPAD_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)
endif()

set(QBREAKPAD_INSTALL_NAME ${PROJECT_NAME})

add_subdirectory(handler)