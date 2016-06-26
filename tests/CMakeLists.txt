find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(tests
	buffer_tests.cc
	tone_tests.cc

	main.cc
)

target_link_libraries(tests

	decomposer_lib

	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

