set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfPhysics/Geometry)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfPhysics/Geometry)

# all source files
set(SRC
    ${INCROOT}/../Settings.hpp
    ${INCROOT}/../Geometry.hpp
    ${INCROOT}/minmax.hpp
    ${INCROOT}/minmax.inl
    ${INCROOT}/angle.hpp
    ${INCROOT}/angle.inl
    ${INCROOT}/trigonometry.hpp
    ${INCROOT}/trigonometry.inl
    ${INCROOT}/vector2.hpp
    ${INCROOT}/vector2.inl
    ${INCROOT}/transformation.hpp
    ${INCROOT}/transformation.inl
    ${INCROOT}/line.hpp
    ${INCROOT}/line.inl
    ${INCROOT}/box.hpp
    ${INCROOT}/box.inl
    ${INCROOT}/triangle.hpp
    ${INCROOT}/triangle.inl
    ${INCROOT}/shape.hpp
    ${INCROOT}/circle.hpp
    ${SRCROOT}/circle.cpp
    ${INCROOT}/rectangle.hpp
    ${SRCROOT}/rectangle.cpp
    ${INCROOT}/polygon.hpp
    ${SRCROOT}/polygon.cpp
    ${INCROOT}/plane.hpp
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

