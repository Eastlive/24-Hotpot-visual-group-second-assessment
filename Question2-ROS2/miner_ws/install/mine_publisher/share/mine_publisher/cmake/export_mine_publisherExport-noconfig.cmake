#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mine_publisher::mine_publisher" for configuration ""
set_property(TARGET mine_publisher::mine_publisher APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mine_publisher::mine_publisher PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmine_publisher.so"
  IMPORTED_SONAME_NOCONFIG "libmine_publisher.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS mine_publisher::mine_publisher )
list(APPEND _IMPORT_CHECK_FILES_FOR_mine_publisher::mine_publisher "${_IMPORT_PREFIX}/lib/libmine_publisher.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
