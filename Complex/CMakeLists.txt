file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${complexlibrary} STATIC ${srcs} ${hdrs})

target_link_libraries(${complexlibrary} ${matrixlibrary})
target_link_libraries(${complexlibrary} ${vectorlibrary})
target_link_libraries(${complexlibrary} ${quantumlibrary})


