set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets 5.6 REQUIRED)
find_package(Qt5Multimedia 5.6 REQUIRED )

add_executable(decomposer
	main.cc
	main_window.cc main_window.hh main_window.ui
	waveform_display.cc waveform_display.hh
	audio_source.cc audio_source.hh
)

target_link_libraries(decomposer

	decomposer_lib

	Qt5::Widgets
	Qt5::Multimedia
)

