
add_executable(decomposer
	main.cc
	main_window.cc main_window.hh main_window.ui
	frequency_meter.cc frequency_meter.hh
)

target_link_libraries(decomposer

	decomposer_lib
	decomposer_widgets

	Qt5::Widgets
	Qt5::Multimedia

	${ESSENTIA_Libraries}
)

