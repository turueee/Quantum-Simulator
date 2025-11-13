cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME QuantumSimulator)
project(${PROJECT_NAME})

set(application Application)
set(stringlibrary String)
set(errorlibrary Error)
set(matrixlibrary Matrix)
set(complexlibrary Complex)
set(vectorlibrary Vector)
set(quantumlibrary Quantum)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/String)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Vector)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Error)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Matrix)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Complex)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Quantum)


add_subdirectory(Main)
add_subdirectory(String)
add_subdirectory(Error)
add_subdirectory(Matrix)
add_subdirectory(Vector)
add_subdirectory(Complex)
add_subdirectory(Quantum)