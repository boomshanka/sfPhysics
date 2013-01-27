# Locate the SFPHYSICS library
#
# This module defines the following variables:
# - For each module XXX (SYSTEM, DEBUGDRAW):
#   - SFPHYSICS_XXX_LIBRARY_DEBUG, the name of the debug library of the xxx module (set to SFPHYSICS_XXX_LIBRARY_RELEASE is no debug version is found)
#   - SFPHYSICS_XXX_LIBRARY_RELEASE, the name of the release library of the xxx module (set to SFPHYSICS_XXX_LIBRARY_DEBUG is no release version is found)
#   - SFPHYSICS_XXX_LIBRARY, the name of the library to link to for the xxx module (includes both debug and optimized names if necessary)
#   - SFPHYSICS_XXX_FOUND, true if either the debug or release library of the xxx module is found
# - SFPHYSICS_LIBRARIES, the list of all libraries corresponding to the required modules
# - SFPHYSICS_FOUND, true if all the required modules are found
# - SFPHYSICS_INCLUDE_DIR, the path where SFPHYSICS headers are located (the directory containing the sfPhysics/Config.hpp file)
#
# By default, the dynamic libraries of SFPHYSICS will be found. To find the static ones instead,
# you must set the SFPHYSICS_STATIC_LIBRARIES variable to TRUE before calling find_package(SFPHYSICS ...).
#
# If SFPHYSICS is not installed in a standard path, you can use the SFPHYSICSDIR CMake variable or environment variable
# to tell CMake where SFPHYSICS is.

# deduce the libraries suffix from the options
set(FIND_SFPHYSICS_LIB_SUFFIX "")
if(SFPHYSICS_STATIC_LIBRARIES)
    set(FIND_SFPHYSICS_LIB_SUFFIX "${FIND_SFPHYSICS_LIB_SUFFIX}-s")
endif()

# find the SFPHYSICS include directory
find_path(SFPHYSICS_INCLUDE_DIR sfphysics/settings
          PATH_SUFFIXES include
          PATHS
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/
          /usr/
          /sw          # Fink
          /opt/local/  # DarwinPorts
          /opt/csw/    # Blastwave
          /opt/
          ${SFPHYSICSDIR}
          $ENV{SFPHYSICSDIR})

# check the version number
set(SFPHYSICS_VERSION_OK TRUE)
if(SFPHYSICS_FIND_VERSION AND SFPHYSICS_INCLUDE_DIR)
    # extract the major and minor version numbers from SFPHYSICS/Config.hpp
    FILE(READ "${SFPHYSICS_INCLUDE_DIR}/sfPhysics/Config.hpp" SFPHYSICS_CONFIG_HPP_CONTENTS)
    STRING(REGEX REPLACE ".*#define SFPHYSICS_VERSION_MAJOR ([0-9]+).*" "\\1" SFPHYSICS_VERSION_MAJOR "${SFPHYSICS_CONFIG_HPP_CONTENTS}")
    STRING(REGEX REPLACE ".*#define SFPHYSICS_VERSION_MINOR ([0-9]+).*" "\\1" SFPHYSICS_VERSION_MINOR "${SFPHYSICS_CONFIG_HPP_CONTENTS}")
    math(EXPR SFPHYSICS_REQUESTED_VERSION "${SFPHYSICS_FIND_VERSION_MAJOR} * 10 + ${SFPHYSICS_FIND_VERSION_MINOR}")

    # if we could extract them, compare with the requested version number
    if (SFPHYSICS_VERSION_MAJOR)
        # transform version numbers to an integer
        math(EXPR SFPHYSICS_VERSION "${SFPHYSICS_VERSION_MAJOR} * 10 + ${SFPHYSICS_VERSION_MINOR}")

        # compare them
        if(SFPHYSICS_VERSION LESS SFPHYSICS_REQUESTED_VERSION)
            set(SFPHYSICS_VERSION_OK FALSE)
        endif()
    else()
        # SFPHYSICS version is < 1.0
        if (SFPHYSICS_REQUESTED_VERSION GREATER 19)
            set(SFPHYSICS_VERSION_OK FALSE)
        endif()
    endif()
endif()

# find the requested modules
set(SFPHYSICS_FOUND TRUE) # will be set to false if one of the required modules is not found
set(FIND_SFPHYSICS_LIB_PATHS ~/Library/Frameworks
                        /Library/Frameworks
                        /usr/local
                        /usr
                        /sw
                        /opt/local
                        /opt/csw
                        /opt
                        ${SFPHYSICSDIR}
                        $ENV{SFPHYSICSDIR})
foreach(FIND_SFPHYSICS_COMPONENT ${SFPHYSICS_FIND_COMPONENTS})
    string(TOLOWER ${FIND_SFPHYSICS_COMPONENT} FIND_SFPHYSICS_COMPONENT_LOWER)
    string(TOUPPER ${FIND_SFPHYSICS_COMPONENT} FIND_SFPHYSICS_COMPONENT_UPPER)
    set(FIND_SFPHYSICS_COMPONENT_NAME SFPHYSICS-${FIND_SFPHYSICS_COMPONENT_LOWER}${FIND_SFPHYSICS_LIB_SUFFIX})

    # debug library
    find_library(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG
                 NAMES ${FIND_SFPHYSICS_COMPONENT_NAME}-d
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_SFPHYSICS_LIB_PATHS})

    # release library
    find_library(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE
                 NAMES ${FIND_SFPHYSICS_COMPONENT_NAME}
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_SFPHYSICS_LIB_PATHS})

    if (SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG OR SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE)
        # library found
        set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_FOUND TRUE)
        
        # if both are found, set SFPHYSICS_XXX_LIBRARY to contain both
        if (SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG AND SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE)
            set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY debug     ${SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG}
                                                          optimized ${SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE})
        endif()

        # if only one debug/release variant is found, set the other to be equal to the found one
        if (SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG AND NOT SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE)
            # debug and not release
            set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE ${SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG})
            set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY         ${SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG})
        endif()
        if (SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE AND NOT SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG)
            # release and not debug
            set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG ${SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE})
            set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY       ${SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE})
        endif()
    else()
        # library not found
        set(SFPHYSICS_FOUND FALSE)
        set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_FOUND FALSE)
        set(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY "")
        set(FIND_SFPHYSICS_MISSING "${FIND_SFPHYSICS_MISSING} SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY")
    endif()

    # mark as advanced
    MARK_AS_ADVANCED(SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY
                     SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_RELEASE
                     SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY_DEBUG)

    # add to the global list of libraries
    set(SFPHYSICS_LIBRARIES ${SFPHYSICS_LIBRARIES} "${SFPHYSICS_${FIND_SFPHYSICS_COMPONENT_UPPER}_LIBRARY}")
endforeach()

# handle errors
if(NOT SFPHYSICS_VERSION_OK)
    # sfPhysics version not ok
    set(FIND_SFPHYSICS_ERROR "SFPHYSICS found but version too low (requested: ${SFPHYSICS_FIND_VERSION}, found: ${SFPHYSICS_VERSION_MAJOR}.${SFPHYSICS_VERSION_MINOR})")
    set(SFPHYSICS_FOUND FALSE)
elseif(NOT SFPHYSICS_FOUND)
    # include directory or library not found
    set(FIND_SFPHYSICS_ERROR "Could NOT find sfPhysics (missing: ${FIND_SFPHYSICS_MISSING})")
endif()
if (NOT SFPHYSICS_FOUND)
    if(SFPHYSICS_FIND_REQUIRED)
        # fatal error
        message(FATAL_ERROR ${FIND_SFPHYSICS_ERROR})
    elseif(NOT SFPHYSICS_FIND_QUIETLY)
        # error but continue
        message("${FIND_SFPHYSICS_ERROR}")
    endif()
endif()

# handle success
if(SFPHYSICS_FOUND)
    message("Found sfPhysics: ${SFPHYSICS_INCLUDE_DIR}")
endif()
