set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfphysics/draw)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfphysics/draw)

# all source files
set(SRC
    ${INCROOT}/../draw.hpp
    ${SRCROOT}/scene.cpp
    ${INCROOT}/scene.hpp
    ${INCROOT}/drawable.hpp
    ${SRCROOT}/drawbody.cpp
    ${INCROOT}/drawbody.hpp
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

