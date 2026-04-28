cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME QuantumSimulator)
project(${PROJECT_NAME} CXX)

find_package(OpenMP REQUIRED)

# === НАСТРОЙКА ФЛАГОВ ДЛЯ RELEASE ===
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /fp:fast /D NDEBUG")
endif()
# ====================================

set(application Application)
set(quantumlibrary Quantum)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Quantum)

add_subdirectory(Main)
add_subdirectory(Quantum)
