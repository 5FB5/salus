cmake_minimum_required(VERSION 3.22)
project(patient LANGUAGES CXX)

set(SOURCES patient.cpp
            patientdatabase.cpp
            patientlistmodel.cpp)


find_package(QT NAMES Qt6 Qt5 COMPONENTS WebEngineWidgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebEngineWidgets PrintSupport REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/libs/PDF-Writer)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

target_link_libraries(${PROJECT_NAME} PRIVATE FreeType)
target_link_libraries(${PROJECT_NAME} PRIVATE LibAesgm)
target_link_libraries(${PROJECT_NAME} PRIVATE LibJpeg)
target_link_libraries(${PROJECT_NAME} PRIVATE LibPng)
target_link_libraries(${PROJECT_NAME} PRIVATE LibTiff)
target_link_libraries(${PROJECT_NAME} PRIVATE PDFWriter)
target_link_libraries(${PROJECT_NAME} PUBLIC Zlib)
