#PACK_NAME, PACK_CONFIG_DIR, PACK_VERSION and PACK_ROOT are all predefined variables for pre and post config files.

set(${PACK_NAME}_LIB_DIR "${PACKAGE_PREFIX_DIR}/lib")

if(NOT TARGET libarchive)

	include(FindLibArchive)
	if(NOT ${LibArchive_FOUND})
		message(FATAL_ERROR "LibArchive could not be found for this configuration. ez-archive cannot be used.")
	endif()

	add_library(libarchive STATIC IMPORTED)
	set_property(TARGET libarchive APPEND PROPERTY IMPORTED_CONFIGURATIONS $<UPPER_CASE:$<CONFIG>>)
	set_target_properties(libarchive PROPERTIES
		IMPORTED_LINK_INTERFACE_LANGUAGES_$<UPPER_CASE:$<CONFIG>> "CXX"
		IMPORTED_LOCATION_$<UPPER_CASE:$<CONFIG>> $<LINK_ONLY:${LibArchive_LIBRARIES}>
	)
	
endif()