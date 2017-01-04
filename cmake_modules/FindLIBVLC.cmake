# This module defines
#  LIBVLC_INCLUDE_DIRS, where to find header, etc.
#  LIBVLC_LIBRARIES, the libraries needed to use curl.
#  LIBVLC_FOUND, If false, do not try to use curl.

find_path(
        LIBVLC_INCLUDE_DIR
        NAMES vlc/vlc.h
        HINTS
        ${LIBVLC_LOCATION}/include
)
message("${LIBVLC_INCLUDE_DIR}")

find_library(
        LIBVLC_LIBVLC
        # names from cmake's FindCURL
        NAMES libvlc
        PATHS
        ${LIBVLC_LOCATION}/lib
)

find_library(
        LIBVLC_LIBVLCCORE
        # names from cmake's FindCURL
        NAMES libvlccore
        PATHS
        ${LIBVLC_LOCATION}/lib
)

set(LIBVLC_INCLUDE_DIRS ${LIBVLC_INCLUDE_DIR})
set(LIBVLC_LIBRARIES ${LIBVLC_LIBVLC} ${LIBVLC_LIBVLCCORE})

# handle the QUIETLY and REQUIRED arguments and set CURL_FOUND to TRUE
# if all listed variables are TRUE, hide their existence from configuration view
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBVLC DEFAULT_MSG
        LIBVLC_INCLUDE_DIRS LIBVLC_LIBRARIES)
mark_as_advanced (LIBVLC_INCLUDE_DIRS LIBVLC_LIBRARIES)