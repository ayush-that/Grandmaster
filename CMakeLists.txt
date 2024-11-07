cmake_minimum_required(VERSION 3.16)
project(Grandmaster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

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

add_executable(Grandmaster ${SOURCES} ${HEADERS})
target_link_libraries(Grandmaster PRIVATE Qt6::Widgets)