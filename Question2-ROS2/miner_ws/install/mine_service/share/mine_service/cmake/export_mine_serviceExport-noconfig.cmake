#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mine_service::mine_service" for configuration ""
set_property(TARGET mine_service::mine_service APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mine_service::mine_service PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmine_service.so"
  IMPORTED_SONAME_NOCONFIG "libmine_service.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS mine_service::mine_service )
list(APPEND _IMPORT_CHECK_FILES_FOR_mine_service::mine_service "${_IMPORT_PREFIX}/lib/libmine_service.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
