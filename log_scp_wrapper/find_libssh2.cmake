if(NOT (LIBSSH2_INCLUDE_DIR AND LIBSSH2_LIB))
  find_package(PkgConfig)
  pkg_check_modules(PC_LIBSSH2 QUIET libssh2)

  find_path(LIBSSH2_INCLUDE_DIR
    NAMES
        libssh2.h
        libssh2_publickey.h
        libssh2_sftp.h
    PATHS
      /usr/include
      /usr/local/include
      /opt/local/include
      /sw/include
    HINTS
        ${PC_LIBSSH2_INCLUDE_DIRS}
        ${PC_LIBSSH2_INCLUDE_DIR}
  )

  find_library(LIBSSH2_LIB
    NAMES
      ssh2
      libssh2
    HINTS
        ${PC_LIBSSH2_LIBDIR}
        ${PC_LIBSSH2_LIBRARY_DIRS}
  )

  mark_as_advanced(LIBSSH2_INCLUDE_DIR LIBSSH2_LIB)
endif(NOT (LIBSSH2_INCLUDE_DIR AND LIBSSH2_LIB))

message("PC_LIBSSH2_FOUND=${PC_LIBSSH2_FOUND}")
message("PC_LIBSSH2_INCLUDE_DIRS=${PC_LIBSSH2_INCLUDE_DIRS}")
message("PC_LIBSSH2_LIBRARIES=${PC_LIBSSH2_LIBRARIES}")
message("PC_LIBSSH2_LINK_LIBRARIES=${PC_LIBSSH2_LINK_LIBRARIES}")
message("PC_LIBSSH2_LIBRARY_DIRS=${PC_LIBSSH2_LIBRARY_DIRS}")
message("PC_LIBSSH2_INCLUDE_DIRS=${PC_LIBSSH2_INCLUDE_DIRS}")
message("PC_LIBSSH2_LIBDIR=${PC_LIBSSH2_LIBDIR}")

message("LIBSSH2_INCLUDE_DIR=${LIBSSH2_INCLUDE_DIR}")
message("LIBSSH2_LIB=${LIBSSH2_LIB}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBSSH2
    FOUND_VAR LIBSSH2_FOUND
    REQUIRED_VARS LIBSSH2_LIB LIBSSH2_INCLUDE_DIR)

if(LIBSSH2_FOUND)
    set(LIBSSH2_LIBS ${LIBSSH2_LIB})
    set(LIBSSH2_INCLUDE_DIRS ${LIBSSH2_INCLUDE_DIR})

    message("Found Libssh2")

endif()
