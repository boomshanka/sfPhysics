set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfphysics/draw)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfphysics/draw)

# all source files
set(SRC
    ${SRCROOT}/bodydraw.cpp
    ${INCROOT}/bodydraw
    ${INCROOT}/drawsettings
)


# define the sfphysics-debugdraw target
sfphysics_add_library(sfphysics-debugdraw
                 SOURCES ${SRC}
                 DEPENDS sfphysics-mechanic sfml-graphics
                 EXTERNAL_LIBS ${DEBUGDRAW_EXT_LIBS})

