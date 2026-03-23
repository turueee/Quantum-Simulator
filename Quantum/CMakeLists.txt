file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${quantumlibrary} STATIC ${srcs} ${hdrs})

