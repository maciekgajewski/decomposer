find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_library(decomposer_lib STATIC
	types.hh
	audio_buffer.cc audio_buffer.hh
)
target_include_directories(decomposer_lib INTERFACE ..)

