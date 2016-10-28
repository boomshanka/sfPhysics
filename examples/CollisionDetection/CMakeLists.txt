set(SRCROOT ${CMAKE_SOURCE_DIR}/examples/CollisionDetection)

# all source files
set(SRC ${SRCROOT}/main.cpp)

# define the example target
sfphysics_add_example(CollisionDetection
                 SOURCES ${SRC}
                 DEPENDS sfml-system sfml-window sfml-graphics sfphysics-geometry sfphysics-mechanics sfphysics-draw)
