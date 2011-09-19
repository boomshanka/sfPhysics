set(SRCROOT ${CMAKE_SOURCE_DIR}/examples/tower)

# all source files
set(SRC ${SRCROOT}/Tower.cpp)

# define the tower target
sfphysics_add_example(tower
                 SOURCES ${SRC}
                 DEPENDS sfml-system sfml-window sfml-graphics sfphysics-mechanic)
