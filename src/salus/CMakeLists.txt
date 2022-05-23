cmake_minimum_required(VERSION 3.14)

project(salus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

add_subdirectory(backend)
add_subdirectory(backend/doctor)
add_subdirectory(backend/patient)

qt5_add_resources(RESOURCES qml.qrc)

set(PROJECT_SOURCES
        main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC backend)

#target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Network)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Quick)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

