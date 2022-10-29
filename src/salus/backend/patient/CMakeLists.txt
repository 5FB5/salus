cmake_minimum_required(VERSION 3.22)
project(patient LANGUAGES CXX)

set(SOURCES patient.cpp
            patientdatabase.cpp
            patientlistmodel.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
