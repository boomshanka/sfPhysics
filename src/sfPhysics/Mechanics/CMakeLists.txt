set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfPhysics/Mechanics)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfPhysics/Mechanics)


# all source files
set(SRC
    ${INCROOT}/../Settings.hpp
    ${INCROOT}/../Mechanics.hpp
    ${INCROOT}/Body.hpp
    ${SRCROOT}/Body.cpp
    ${INCROOT}/MaterialDef.hpp
    ${SRCROOT}/MaterialDef.cpp
    ${INCROOT}/Collider.hpp
    ${SRCROOT}/Collider.cpp
    ${INCROOT}/Contact.hpp
    ${SRCROOT}/Contact.cpp
)


# define the sfphysics-mechanics target
sfphysics_add_library(sfphysics-mechanics
	SOURCES ${SRC}
	DEPENDS sfphysics-geometry)

