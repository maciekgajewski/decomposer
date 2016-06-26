add_library(decomposer_widgets_plugin SHARED
	widgets_plugin.cc widgets_plugin.hh
)

target_link_libraries(decomposer_widgets_plugin

	decomposer_widgets

	${ESSENTIA_Libraries}
)

set_target_properties(decomposer_widgets_plugin
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/plugins/designer)
