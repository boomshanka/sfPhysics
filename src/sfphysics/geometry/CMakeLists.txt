set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfphysics/geometry)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfphysics/geometry)

# all source files
set(SRC
    ${INCROOT}/../settings
    ${INCROOT}/angle
    ${INCROOT}/angle.inl
    ${INCROOT}/trigonometry
    ${INCROOT}/trigonometry.inl
    ${INCROOT}/math
    ${INCROOT}/math.inl
    ${INCROOT}/vector2
    ${INCROOT}/vector2.inl
    ${INCROOT}/matrix
    ${INCROOT}/matrix.inl
    ${INCROOT}/line
    ${INCROOT}/line.inl
    ${INCROOT}/triangle
    ${INCROOT}/triangle.inl
    ${INCROOT}/form
    ${INCROOT}/circle
    ${SRCROOT}/circle.cpp
    ${INCROOT}/rectangle
    ${SRCROOT}/rectangle.cpp
    ${INCROOT}/polygon
    ${SRCROOT}/polygon.cpp
    ${INCROOT}/plane
    ${SRCROOT}/plane.cpp
)

# add SFML source
if(SFML_ENABLED)
    set(SRC
        ${SRC}
        ${SFML_INCLUDE_DIR}/SFML/System/Vector2.hpp
        ${SFML_INCLUDE_DIR}/SFML/System/Vector2.inl
    )
else()
    set(SRC
        ${SRC}
        ${INCROOT}/../SFML_System/Vector2.hpp
        ${INCROOT}/../SFML_System/Vector2.inl
    )
endif()


# define the sfphysics-geometry target
sfphysics_add_library(sfphysics-geometry SOURCES ${SRC})

