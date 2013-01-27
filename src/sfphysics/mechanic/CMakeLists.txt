set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfphysics/mechanic)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfphysics/mechanic)


# all source files
set(SRC
    ${INCROOT}/properties
    ${INCROOT}/properties.inl
    ${INCROOT}/shape
    ${SRCROOT}/shape.cpp
    ${INCROOT}/body
    ${SRCROOT}/body.cpp
#    ${INCROOT}/
#    ${SRCROOT}/
)


# define the sfphysics-system target
sfphysics_add_library(sfphysics-mechanic
                 SOURCES ${SRC}
                 DEPENDS sfphysics-geometry)

