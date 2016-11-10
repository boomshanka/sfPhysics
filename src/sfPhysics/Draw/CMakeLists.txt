set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfPhysics/Draw)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfPhysics/Draw)

# all source files
set(SRC
    ${INCROOT}/../Draw.hpp
    ${SRCROOT}/Scene.cpp
    ${INCROOT}/Scene.hpp
    ${INCROOT}/Drawable.hpp
    ${SRCROOT}/Drawbody.cpp
    ${INCROOT}/Drawbody.hpp
    ${SRCROOT}/ShapeDrawer.cpp
    ${INCROOT}/ShapeDrawer.hpp
    ${SRCROOT}/GeometryDrawer.cpp
    ${INCROOT}/GeometryDrawer.hpp
)


# define the sfphysics-debugdraw target
sfphysics_add_library(sfphysics-draw
                 SOURCES ${SRC}
                 DEPENDS sfphysics-geometry sfphysics-mechanics sfml-graphics
                 EXTERNAL_LIBS ${DEBUGDRAW_EXT_LIBS})

