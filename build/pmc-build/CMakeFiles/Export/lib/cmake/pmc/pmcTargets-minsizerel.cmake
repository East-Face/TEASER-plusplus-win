#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pmc::pmc" for configuration "MinSizeRel"
set_property(TARGET pmc::pmc APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(pmc::pmc PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/pmc.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS pmc::pmc )
list(APPEND _IMPORT_CHECK_FILES_FOR_pmc::pmc "${_IMPORT_PREFIX}/lib/pmc.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
