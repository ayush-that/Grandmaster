cmake_minimum_required(VERSION 3.16)
project(Grandmaster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg Multimedia)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/styles/style.qss
               ${CMAKE_CURRENT_BINARY_DIR}/style.qss COPYONLY)

set(SOURCES
    src/main.cpp
    src/chessboard.cpp
    src/piece.cpp
)

set(HEADERS
    include/chessboard.h
    include/piece.h
    include/constants.h
)

add_executable(Grandmaster
    src/main.cpp
    src/chessboard.cpp
    include/chessboard.h
    qresource.qrc
)

target_link_libraries(Grandmaster PRIVATE Qt6::Widgets Qt6::Svg Qt6::Multimedia)