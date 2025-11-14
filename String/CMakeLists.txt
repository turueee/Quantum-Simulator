file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${stringlibrary} STATIC ${srcs} ${hdrs})

target_link_libraries(${stringlibrary} ${matrixlibrary})
target_link_libraries(${stringlibrary} ${errorlibrary})
target_link_libraries(${stringlibrary} ${complexlibrary})



