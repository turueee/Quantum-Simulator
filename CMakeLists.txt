cmake_minimum_required(VERSION 3.5)

# Указываем, что это C++ проект (полезно для правильной настройки флагов)
set(PROJECT_NAME QuantumSimulator)
project(${PROJECT_NAME} CXX)

# === НАСТРОЙКА ФЛАГОВ ДЛЯ RELEASE ===
# Переопределяем стандартный -O3 на -O2
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
elseif(MSVC)
    # Для Visual Studio эквивалентом является /O2
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /D NDEBUG")
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