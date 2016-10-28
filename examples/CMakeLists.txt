# add the examples subdirectories

##add_subdirectory(geometry_test)

if(SFML_ENABLED)
	add_subdirectory(GeometryUnitTest)
	add_subdirectory(CollisionDetection)
#	add_subdirectory(PhysicsLoop)
endif()

