#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tinyply" for configuration "Debug"
set_property(TARGET tinyply APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(tinyply PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/tinyplyd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/tinyplyd.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS tinyply )
list(APPEND _IMPORT_CHECK_FILES_FOR_tinyply "${_IMPORT_PREFIX}/lib/tinyplyd.lib" "${_IMPORT_PREFIX}/bin/tinyplyd.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
