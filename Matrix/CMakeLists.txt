file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${matrixlibrary} STATIC ${srcs} ${hdrs})

target_link_libraries(${matrixlibrary} ${errorlibrary})
target_link_libraries(${matrixlibrary} ${complexlibrary})
