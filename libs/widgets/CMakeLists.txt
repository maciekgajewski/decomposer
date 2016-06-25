

add_library(decomposer_widgets STATIC
	waveform_display.cc waveform_display.hh
	spectrum_display.cc spectrum_display.hh
)

target_include_directories(decomposer_widgets INTERFACE ..)

target_link_libraries(decomposer_widgets

	decomposer_lib
	Qt5::Widgets
)
