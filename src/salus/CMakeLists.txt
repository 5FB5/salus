cmake_minimum_required(VERSION 3.22)

project(salus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets Gui PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets Gui PrintSupport REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/libs/PDF-Writer)

add_subdirectory(backend)
add_subdirectory(backend/doctor)
add_subdirectory(backend/patient)
add_subdirectory(libs/PDF-Writer)

qt5_add_resources(RESOURCES qml.qrc)

set(PROJECT_SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC backend)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Network)

target_link_libraries(${PROJECT_NAME} PRIVATE FreeType)
target_link_libraries(${PROJECT_NAME} PRIVATE LibAesgm)
target_link_libraries(${PROJECT_NAME} PRIVATE LibJpeg)
target_link_libraries(${PROJECT_NAME} PRIVATE LibPng)
target_link_libraries(${PROJECT_NAME} PRIVATE LibTiff)
target_link_libraries(${PROJECT_NAME} PRIVATE PDFWriter)
target_link_libraries(${PROJECT_NAME} PRIVATE Zlib)

