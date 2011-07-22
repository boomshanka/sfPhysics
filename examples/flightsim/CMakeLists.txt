set(SRCROOT ${CMAKE_SOURCE_DIR}/examples/flightsim)

# all source files
set(SRC ${SRCROOT}/Main.cpp
		${SRCROOT}/Sim.cpp
		${SRCROOT}/Sim.hpp
		)

# define the moonlander target
sfphysics_add_example(flightsim
                 SOURCES ${SRC}
                 DEPENDS sfml-system sfml-window sfml-graphics sfphysics-system)
