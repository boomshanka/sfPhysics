cmake_minimum_required(VERSION 2.8)

# set a default build type if none was provided
# this has to be done before the project() instruction!
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project name
project(sfPhysics)

# include the configuration file
include(${CMAKE_SOURCE_DIR}/cmake/Config.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Macros.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules/)
find_package(SFML 2.0 REQUIRED system graphics)


# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# add the sfPhysics header path
include_directories(${CMAKE_SOURCE_DIR}/include)

# add an option for choosing the build type (shared or static)
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "TRUE to build sfPhysics as shared libraries, FALSE to build it as static libraries")

# add an option for building the examples
set(BUILD_EXAMPLES TRUE CACHE BOOL "TRUE to build the sfPhysics 
examples, FALSE to ignore them")

# add an option for building the API documentation
set(BUILD_DOC FALSE CACHE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

# add an option for building the libarie with SFML
set(SFML_ENABLED TRUE CACHE BOOL "TRUE to build sfPhysics with functions 
for SFML and with the debugdraw pack")


#
if(NOT SFML_FOUND)
    set(SFML_ENABLED FALSE)
endif()


# define SFPHYSICS_STATIC if the build type is not set to 'shared'
if(NOT BUILD_SHARED_LIBS)
    add_definitions(-DSFPHYSICS_STATIC)
endif()


# define SFML_ENDABLED
if(SFML_ENABLED)
    add_definitions(-DSFML_ENABLED)
endif()


# disable the rpath stuff
set(CMAKE_SKIP_BUILD_RPATH TRUE)

# add the subdirectories
add_subdirectory(src/sfphysics)

# setup the install rules
install(DIRECTORY include
        DESTINATION .
        COMPONENT devel
        PATTERN "*~" EXCLUDE
        PATTERN ".git" EXCLUDE)
install(FILES cmake/Modules/FindSfPhysics.cmake DESTINATION ${CMAKE_ROOT}/Modules)
install(FILES LICENSE DESTINATION ${INSTALL_MISC_DIR})


if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
##if(BUILD_DOC)
##    add_subdirectory(doc)
##endif()


