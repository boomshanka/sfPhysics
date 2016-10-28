set(SRCROOT ${CMAKE_SOURCE_DIR}/examples/GeometryUnitTest)

# all source files
set(SRC ${SRCROOT}/main.cpp)

# define the example target
sfphysics_add_example(GeometryUnitTest
                 SOURCES ${SRC}
                 DEPENDS sfml-system sfml-window sfml-graphics sfphysics-geometry)
