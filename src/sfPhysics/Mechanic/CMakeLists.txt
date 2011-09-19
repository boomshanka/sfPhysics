set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfPhysics/Mechanic)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfPhysics/Mechanic)


# all source files
set(SRC
    ${INCROOT}/../Settings.hpp
    ${INCROOT}/../SFML_Graphics.hpp
    ${SRCROOT}/CollisionManager.cpp
    ${INCROOT}/CollisionManager.hpp
    ${SRCROOT}/Collision.cpp
    ${INCROOT}/Collision.hpp
    ${SRCROOT}/Contact.cpp
    ${INCROOT}/Contact.hpp
    ${SRCROOT}/Environment.cpp
    ${INCROOT}/Environment.hpp
    
    ${SRCROOT}/Hinge.cpp
    ${INCROOT}/Hinge.hpp
    ${SRCROOT}/Objects.cpp
    ${INCROOT}/Objects.hpp
    ${SRCROOT}/Physicable.cpp
    ${INCROOT}/Physicable.hpp
    ${SRCROOT}/SeparatingAxis.cpp
    ${INCROOT}/SeparatingAxis.hpp
    ${SRCROOT}/Shape.cpp
    ${INCROOT}/Shape.hpp
    ${SRCROOT}/ShapeManager.cpp
    ${INCROOT}/ShapeManager.hpp
    ${SRCROOT}/Spring.cpp
    ${INCROOT}/Spring.hpp
    ${INCROOT}/CollisionEvent.hpp
    ${INCROOT}/Linkable.hpp
    ${INCROOT}/ObjectList.hpp
)

# add SFML source
if(SFML_ENABLED)
    set(SRC
        ${SRC}
#        ${SFML_INCLUDE_DIR}/SFML/System/Vector2.hpp
#        ${SFML_INCLUDE_DIR}/SFML/System/Vector2.inl
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Drawable.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Shape.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Sprite.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Shader.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Text.hpp
    )
else()
    set(SRC
        ${SRC}
#        ${INCROOT}/../SFML_System/Vector2.hpp
#        ${INCROOT}/../SFML_System/Vector2.inl
    )
endif()


# define the sfphysics-system target
sfphysics_add_library(sfphysics-mechanic
                 SOURCES ${SRC})  ##
                 ##EXTERNAL_LIBS ${SYSTEM_EXT_LIBS})

