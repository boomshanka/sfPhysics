#include <sfPhysics/System/Environment.hpp>



sfp::Environment::Environment()
: myGravity(sf::Vector2f(0,10)), myTimefactor(1), myLengthfactor(1), myFrameTime(0)
{
	
}


sfp::Environment::~Environment()
{

}



//--------------------------------------------------------------------------------//



void sfp::Environment::RenderGravity()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		(*it)->AddSpeed(myGravity*myFrameTime);
	}
}



void sfp::Environment::MoveObjects(bool moovedrawables)
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		(*it)->Rotate((*it)->GetRotationSpeed()*myFrameTime*myTimefactor);
		(*it)->Move((*it)->GetSpeed()*myFrameTime*myTimefactor);
	}
	
	#ifdef SFML_ENABLED
	if(moovedrawables)
		MoveDrawables();
	#endif
}



#ifdef SFML_ENABLED

void sfp::Environment::MoveDrawables()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		if((*it)->GetDrawable()!=NULL)
		{
			(*it)->GetDrawable()->SetPosition((*it)->GetPosition()*myLengthfactor);
			(*it)->GetDrawable()->SetRotation((*it)->GetRotation());
		}
	}
}

#endif


