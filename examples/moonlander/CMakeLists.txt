set(SRCROOT ${CMAKE_SOURCE_DIR}/examples/moonlander)

# all source files
set(SRC ${SRCROOT}/Moonlander.cpp)

# define the moonlander target
sfphysics_add_example(moonlander
                 SOURCES ${SRC}
                 DEPENDS sfml-system sfml-window sfml-graphics sfphysics-system)
