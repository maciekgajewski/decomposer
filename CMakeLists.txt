project(decomposer)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CSS_STANDARD_REQUIRED 1)

find_package(Qt5Widgets 5.6 REQUIRED)
find_package(Qt5Multimedia 5.6 REQUIRED )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(ESSENTIA_Libraries essentia fftw3 swresample avformat avcodec avutil yaml samplerate tag fftw3f)


add_subdirectory(libs)
add_subdirectory(tests)

add_subdirectory(decomposer)
add_subdirectory(guitar_tuner)

