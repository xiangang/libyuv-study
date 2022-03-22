cmake_minimum_required(VERSION 3.10.2)
project(main VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories("${CMAKE_SOURCE_DIR}/lib")

message("include_directories ---> ${CMAKE_SOURCE_DIR}/3rd/libyuv/include")
message("link_directories ---> ${CMAKE_SOURCE_DIR}/3rd/libyuv/lib")

add_executable(main main.c)

target_link_libraries(${PROJECT_NAME} libyuv.so)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
