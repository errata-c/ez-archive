find_package(fmt CONFIG REQUIRED)

add_executable(ez-archive-test "test.cpp")

target_link_libraries(ez-archive-test PRIVATE ez-archive fmt::fmt)

file(COPY
	"${CMAKE_CURRENT_LIST_DIR}/assets/sprites.7z"
	DESTINATION
	"${CMAKE_CURRENT_BINARY_DIR}"
)