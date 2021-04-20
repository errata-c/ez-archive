cmake_minimum_required(VERSION 3.15)

project(EZ_ARCHIVE
VERSION 0.1.1
LANGUAGES CXX)

include(GNUInstallDirs)
include("cmake/ez-cmake/install-package.cmake")

option(BUILD_TESTS "Build the test executables" ON)
option(SEPARATE_DIRECTORY "Install the package into its own directory" ON)
set(CONFIG_DIR "${CMAKE_INSTALL_DATAROOTDIR}/ez-archive" CACHE STRING "The relative directory to install package config files.")



include(FindLibArchive)
if(NOT ${LibArchive_FOUND})
	message(FATAL_ERROR "LibArchive was not found!")
endif()

# Create a target for libarchive, We will have to recreate the target in the preconfig to make sure ez-archive works properly.
add_library(libarchive STATIC IMPORTED)
set_property(TARGET libarchive APPEND PROPERTY IMPORTED_CONFIGURATIONS $<UPPER_CASE:$<CONFIG>>)
set_target_properties(libarchive PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${LibArchive_INCLUDE_DIRS}>
	IMPORTED_LINK_INTERFACE_LANGUAGES_$<UPPER_CASE:$<CONFIG>> "CXX"
	IMPORTED_LOCATION_$<UPPER_CASE:$<CONFIG>> ${LibArchive_LIBRARIES}
  )

# Create ez-archive target.

set(EZ_ARCHIVE_CMAKE_DIR "share/ez-archive/cmake" CACHE STRING "Relative install dir for package config")

add_library(ez-archive STATIC "src/ReadArchive.cpp" "src/WriteArchive.cpp" "src/Defines.cpp")

target_compile_features(ez-archive PUBLIC cxx_std_11)

target_compile_definitions(ez-archive PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)

target_link_libraries(ez-archive 
	PRIVATE 
		libarchive
)

target_include_directories(ez-archive 
PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" 
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>" 
)

if(BUILD_TESTS)
	add_subdirectory("test")
endif()

install(
DIRECTORY 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/"
DESTINATION 
	"${CMAKE_INSTALL_INCLUDEDIR}"
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" 
)

install(TARGETS
        ez-archive
    EXPORT ez-archive-targets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
)

install_package(
	NAME "ez-archive"
	DESTINATION "${CONFIG_DIR}"
	EXPORT "ez-archive-targets"
	VERSION "${EZ_ARCHIVE_VERSION}"
	COMPATIBILITY "SameMajorVersion"
	PRECONFIG "${CMAKE_CURRENT_LIST_DIR}/cmake/preconfig.cmake"
)