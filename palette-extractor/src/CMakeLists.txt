cmake_minimum_required(VERSION 3.16)
project(palette-extractor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(palette-extractor
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
    )
    target_link_libraries(palette-extractor PRIVATE Qt6::Widgets)
else()
    add_executable(palette-extractor
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
    )
    target_link_libraries(palette-extractor PRIVATE Qt5::Widgets)
endif()

set_target_properties(palette-extractor PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
