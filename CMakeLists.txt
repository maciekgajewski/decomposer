project(decomposer)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CSS_STANDARD_REQUIRED 1)

find_package(Qt5Widgets 5.6 REQUIRED)
find_package(Qt5Multimedia 5.6 REQUIRED )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(decomposer)
add_subdirectory(libs)
add_subdirectory(tests)

