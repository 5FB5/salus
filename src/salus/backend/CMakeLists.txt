cmake_minimum_required(VERSION 3.20)
project(backend LANGUAGES CXX)

set(SOURCES backend.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

target_link_libraries(${PROJECT_NAME} PRIVATE doctor)
target_link_libraries(${PROJECT_NAME} PRIVATE patient)
