# Renderer unit test app
add_executable(rotation_test
	main.cpp
)

set_target_properties(rotation_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Special access to Box2D internals for testing
target_include_directories(rotation_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(rotation_test PRIVATE tren)