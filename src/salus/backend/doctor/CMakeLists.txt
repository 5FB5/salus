cmake_minimum_required(VERSION 3.14)
project(doctor LANGUAGES CXX)

set(SOURCES doctor.cpp doctordatabase.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
