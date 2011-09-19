set(SRCROOT ${CMAKE_SOURCE_DIR}/examples/rocket)

# all source files
set(SRC ${SRCROOT}/Rocket.cpp)

# define the rocket target
sfphysics_add_example(rocket
                 SOURCES ${SRC}
                 DEPENDS sfml-system sfml-window sfml-graphics sfphysics-mechanic)
