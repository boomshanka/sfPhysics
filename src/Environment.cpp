#include "Environment.hpp"


sfp::Environment::Environment()
: myGravity(sf::Vector2f(0,100)), myTimefactor(1)
{
	
}


sfp::Environment::~Environment()
{

}



//--------------------------------------------------------------------------------//



void sfp::Environment::ReceiveFrameTime()
{
	sfp::Time::ElapsedTime=sfp::Time::Frametime.GetElapsedTime()*myTimefactor;
	sfp::Time::Frametime.Reset();
}



float sfp::Environment::GetFrameTime()
{
	return sfp::Time::ElapsedTime;
}



void sfp::Environment::AddObject(sfp::Object& newobject)
{
	myObjects.push_back(&newobject);
}



void sfp::Environment::RenderGravity()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		(*it)->SetImpulse((*it)->GetImpulse()+(myGravity*sfp::Time::ElapsedTime));
	}
}



void sfp::Environment::MoveObjects(bool moovedrawables)
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		(*it)->SetRotation((*it)->GetRotation()+(*it)->GetRotationSpeed()*sfp::Time::ElapsedTime*myTimefactor);
		(*it)->Move((*it)->GetSpeed()*sfp::Time::ElapsedTime*myTimefactor);
	}
	
	#ifdef SFML_GRAPHICS_ENABLED
	if(moovedrawables)
		MoveDrawables();
	#endif
}



#ifdef SFML_GRAPHICS_ENABLED

void sfp::Environment::MoveDrawables()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		if((*it)->GetDrawable()!=NULL)
		{
			//(*it)->GetDrawable()->Move((*it)->GetSpeed()*sfp::Time::ElapsedTime*myTimefactor); // das hier geht, das untere verschiebt das objekt //
			(*it)->GetDrawable()->SetPosition((*it)->GetPosition());// FIXME scheint nicht zu gehn, wa?
			(*it)->GetDrawable()->SetRotation((*it)->GetRotation());
		}
	}
}

#endif


