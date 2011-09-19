set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfPhysics/Debugdraw)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfPhysics/Debugdraw)

# all source files
set(SRC
    ${SRCROOT}/ObjectRenderer.cpp
    ${INCROOT}/ObjectRenderer.hpp
    ${INCROOT}/DebugRenderer.hpp
    ${INCROOT}/EventRenderer.hpp
)


# define the sfphysics-debugdraw target
sfphysics_add_library(sfphysics-debugdraw
                 SOURCES ${SRC}
                 DEPENDS sfphysics-mechanic sfml-graphics
                 EXTERNAL_LIBS ${DEBUGDRAW_EXT_LIBS})

