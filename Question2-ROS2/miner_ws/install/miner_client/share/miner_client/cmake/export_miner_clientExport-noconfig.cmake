#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "miner_client::miner_client" for configuration ""
set_property(TARGET miner_client::miner_client APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(miner_client::miner_client PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libminer_client.so"
  IMPORTED_SONAME_NOCONFIG "libminer_client.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS miner_client::miner_client )
list(APPEND _IMPORT_CHECK_FILES_FOR_miner_client::miner_client "${_IMPORT_PREFIX}/lib/libminer_client.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
