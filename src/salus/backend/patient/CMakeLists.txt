cmake_minimum_required(VERSION 3.14)
project(patient LANGUAGES CXX)

set(SOURCES patient.cpp patientdatabase.cpp patientlistmodel.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
