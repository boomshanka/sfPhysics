set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfphysics/mechanics)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfphysics/mechanics)


# all source files
set(SRC
    ${INCROOT}/body.hpp
    ${SRCROOT}/body.cpp
    ${INCROOT}/materialdef.hpp
    ${SRCROOT}/materialdef.cpp
    ${INCROOT}/Collider.hpp
    ${SRCROOT}/Collider.cpp
    ${INCROOT}/Contact.hpp
    ${SRCROOT}/Contact.cpp
)


# define the sfphysics-mechanics target
sfphysics_add_library(sfphysics-mechanics
	SOURCES ${SRC}
	DEPENDS sfphysics-geometry)

