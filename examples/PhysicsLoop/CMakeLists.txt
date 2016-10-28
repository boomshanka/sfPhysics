set(SRCROOT ${CMAKE_SOURCE_DIR}/examples/PhysicsLoop)

# all source files
set(SRC ${SRCROOT}/main.cpp)

# define the example target
sfphysics_add_example(PhysicsLoop
                 SOURCES ${SRC}
                 DEPENDS sfml-system sfml-window sfml-graphics sfphysics-mechanic)
