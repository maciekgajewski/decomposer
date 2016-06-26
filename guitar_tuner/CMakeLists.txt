add_executable(guitar_tuner
	main.cc
	guitar_tuner_window.cc  guitar_tuner_window.hh  guitar_tuner_window.ui
	frequency_meter.cc frequency_meter.hh
)

target_link_libraries(guitar_tuner

	decomposer_lib
	decomposer_widgets

	Qt5::Widgets
	Qt5::Multimedia

	essentia
	fftw3 swresample avformat avcodec avutil yaml samplerate tag fftw3f
)

