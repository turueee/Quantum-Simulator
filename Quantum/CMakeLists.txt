file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${quantumlibrary} STATIC ${srcs} ${hdrs})

target_link_libraries(${quantumlibrary} ${stringlibrary})
target_link_libraries(${quantumlibrary} ${matrixlibrary})
target_link_libraries(${quantumlibrary} ${complexlibrary})
target_link_libraries(${quantumlibrary} ${stringlibrary})
