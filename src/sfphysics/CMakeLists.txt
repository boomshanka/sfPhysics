# include the sfPhysics specific macros
include(${CMAKE_SOURCE_DIR}/cmake/Macros.cmake)

# let CMake know about our additional libraries paths (on Windows and OS X) (shit..)
if (WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers")
    if(COMPILER_GCC)
        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-mingw")
        if(ARCH_32BITS)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/bin/x86")
        else()
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/bin/x64")
        endif()
    elseif(COMPILER_MSVC)
        if(ARCH_32BITS)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-msvc/x86")
        else()
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-msvc/x64")
        endif()
    endif()
elseif(MACOSX)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-osx/lib/")
endif()

# add the sfPhysics sources path (?)
include_directories(${CMAKE_SOURCE_DIR}/src)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# set the output directory for sfPhysics libraries
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

# define the export symbol ??
add_definitions(-DSFPHYSICS_EXPORTS)

# add the modules subdirectories
add_subdirectory(geometry)
add_subdirectory(mechanics)
# add draw module if SFML is enabled
if(SFML_ENABLED)
    add_subdirectory(draw)
endif()


