add_executable(guitar_tuner
	main.cc
)

target_link_libraries(guitar_tuner

	decomposer_lib
	decomposer_widgets

	Qt5::Widgets
	Qt5::Multimedia

	essentia
	fftw3 swresample avformat avcodec avutil yaml samplerate tag fftw3f
)

