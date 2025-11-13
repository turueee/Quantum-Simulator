file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")
add_executable(${application} ${srcs} ${hdrs})

target_link_libraries(${application} ${stringlibrary})
target_link_libraries(${application} ${matrixlibrary})
target_link_libraries(${application} ${vectorlibrary})
target_link_libraries(${application} ${complexlibrary})
target_link_libraries(${application} ${quantumlibrary})
target_link_libraries(${application} ${stringlibrary})

#add_library(${MyLib1} STATIC ${srcs} ${hdrs})


