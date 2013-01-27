set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfPhysics/Electronic)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfPhysics/Electronic)


# all source files
set(SRC
    ${INCROOT}/
)


# define the sfphysics-electronic target
sfphysics_add_library(sfphysics-electronic
                 SOURCES ${SRC})##
                 ##EXTERNAL_LIBS ${ELECTRONIC_EXT_LIBS})

