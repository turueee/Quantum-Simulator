cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME QuantumSimulator)
project(${PROJECT_NAME})

set(application Application)
set(quantumlibrary Quantum)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Quantum)


add_subdirectory(Main)
add_subdirectory(Quantum)