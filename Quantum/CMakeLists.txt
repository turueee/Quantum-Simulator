file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${quantumlibrary} STATIC ${srcs} ${hdrs})
target_link_libraries(${quantumlibrary} PUBLIC OpenMP::OpenMP_CXX)

