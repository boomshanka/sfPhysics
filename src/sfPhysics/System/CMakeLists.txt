# define the sfml-main target
#add_library(sfml-main STATIC ${CMAKE_SOURCE_DIR}/src/SFML/Main/SFML_Main.cpp)


set(INCROOT ${CMAKE_SOURCE_DIR}/include/sfPhysics/System)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sfPhysics/System)


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
    ${INCROOT}/Line.hpp
    ${INCROOT}/Line.inl
    ${INCROOT}/Vector2.hpp
    ${INCROOT}/Vector2.inl
    ${INCROOT}/CollisionEvent.hpp
    ${INCROOT}/Linkable.hpp
    ${INCROOT}/ObjectList.hpp
    ${INCROOT}/../Settings.hpp
    ${INCROOT}/../SFML_Graphics.hpp
)

# add SFML source
if(SFML_ENABLED)
    set(SRC
        ${SRC}
        ${SFML_INCLUDE_DIR}/SFML/System/Vector2.hpp
        ${SFML_INCLUDE_DIR}/SFML/System/Vector2.inl
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Drawable.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Shape.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Sprite.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Shader.hpp
        ${SFML_INCLUDE_DIR}/SFML/Graphics/Text.hpp
    )
else()
    set(SRC
        ${SRC}
        ${INCROOT}/../SFML_System/Vector2.hpp
        ${INCROOT}/../SFML_System/Vector2.inl
    )
endif()


# define the sfphysics-system target
sfphysics_add_library(sfphysics-system
                 SOURCES ${SRC})##
                 ##EXTERNAL_LIBS ${SYSTEM_EXT_LIBS})

