/******************************************************************************
 **	sfPhysics - A simple 2D physics engine
 ** Copyright (C) 2011  Olaf Vogt aka Boomshanka
 ** 
 ** This program is free software; you can redistribute it and/or modify it
 ** under the terms of the GNU General Public License as published by the Free
 ** Software Foundation; either version 3 of the License, or (at your option)
 ** any later version. 
 ** 
 ** This program is distributed in the hope that it will be useful, but WITHOUT
 ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 ** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 ** more details. 
 ** 
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/


#include <sfPhysics/System/CollisionManager.hpp>


#define myObjects ObjectList::myObjectList



sfp::CollisionManager::CollisionManager()
{

}


sfp::CollisionManager::~CollisionManager()
{

}



void sfp::CollisionManager::UpdateCollisions()
{
	for(std::list<sfp::Object*>::iterator it = myObjects.begin(); it != myObjects.end(); ++it)
	{
		std::list<sfp::Object*>::iterator it2 = it;
		for(++it2; it2 != myObjects.end(); ++it2)
		{
			sfp::CollisionEvent event(*it, *it2);
			while(myCollision.GetCollisions(event))
			{
				switch(event.CollisionType)
				{
					case sfp::NoCollision:
						OnNoCollision(event);
					break;
				
					case sfp::BoundingBoxCollision:
						OnBoundingBoxCollision(event);
					break;
				
					case sfp::PreciseCollision:
						OnPreciseCollision(event);
					break;
				}
				
				event = sfp::CollisionEvent(*it, *it2);
			}
		}
	}
}



void sfp::CollisionManager::CollisionResponse(sfp::CollisionEvent& event)
{
	event.R1 = event.Collisionpoint - event.first->GetPosition();
	event.R2 = event.Collisionpoint - event.second->GetPosition();
	
	if(event.first->IsFixed())
	{
		event.Movement = event.second->GetMovement(event.second->ToLocal(event.Collisionpoint));//, -*Normal);//FIXME
	}
	else if(event.second->IsFixed())
	{
		event.Movement = -event.first->GetMovement(event.first->ToLocal(event.Collisionpoint));//, *Normal);
	}
	else
	{
		event.Movement = event.second->GetMovement(event.second->ToLocal(event.Collisionpoint))-//, -*Normal) -
						event.first->GetMovement(event.first->ToLocal(event.Collisionpoint));//, *Normal);
	}
	
	Bounce(event);
	/*event.Friction = */Friction(event);
}


void sfp::CollisionManager::Bounce(sfp::CollisionEvent& event)
{
	if(event.first->IsFixed())
	{	
		event.Impulse = (1 + event.first->GetRestitution() * event.second->GetRestitution()) * DotProduct(event.Movement, event.Collisionnormal);
		event.Impulse /= 1.f/event.second->GetMass() +
				std::abs(DotProduct((1.f/event.second->GetInertiaMoment() * CrossProduct(event.R2, event.Collisionnormal) * event.R2), event.Collisionnormal));
	
		event.second->SetVelocity(event.second->GetVelocity() - (event.Impulse/event.second->GetMass()) * event.Collisionnormal);
		event.second->SetRotationVelocity(event.second->GetRotationVelocity() -
				event.Impulse/event.second->GetInertiaMoment() * CrossProduct(event.R2, event.Collisionnormal) * 180.f/static_cast<float>(M_PI));
		
		event.second->AddIntersection(-event.Intersection, sf::Vector2f()); //FIXME
	}
	else if(event.second->IsFixed())
	{
		event.Impulse = -(1 + event.first->GetRestitution() * event.second->GetRestitution()) * DotProduct(event.Movement, event.Collisionnormal);
		event.Impulse /= 1.f/event.first->GetMass() +
				std::abs(DotProduct((1.f/event.first->GetInertiaMoment() * CrossProduct(event.R1, event.Collisionnormal) * event.R1), event.Collisionnormal));
	
		event.first->SetVelocity(event.first->GetVelocity() - (event.Impulse/event.first->GetMass()) * event.Collisionnormal);
		event.first->SetRotationVelocity(event.first->GetRotationVelocity() -
				event.Impulse/event.first->GetInertiaMoment() * CrossProduct(event.R1, event.Collisionnormal) * 180.f/static_cast<float>(M_PI));
		
		event.first->AddIntersection(event.Intersection, sf::Vector2f()); //FIXME
	}
	else
	{
		event.Impulse = -(1 + event.first->GetRestitution() * event.second->GetRestitution()) * DotProduct(event.Movement, event.Collisionnormal);
		event.Impulse /= 1.f/event.first->GetMass() + 1.f/event.second->GetMass() +
				std::abs(DotProduct((1.f/event.first->GetInertiaMoment() * CrossProduct(event.R1, event.Collisionnormal) * event.R1 +
						1.f/event.second->GetInertiaMoment() * CrossProduct(event.R2, event.Collisionnormal) * event.R2), event.Collisionnormal));
		
		event.first->SetVelocity(event.first->GetVelocity() - (event.Impulse/event.first->GetMass()) * event.Collisionnormal);
		event.second->SetVelocity(event.second->GetVelocity() + (event.Impulse/event.second->GetMass()) * event.Collisionnormal);
		
		event.first->SetRotationVelocity(event.first->GetRotationVelocity() -
				event.Impulse/event.first->GetInertiaMoment() * CrossProduct(event.R1, event.Collisionnormal) * 180.f/static_cast<float>(M_PI));
		event.second->SetRotationVelocity(event.second->GetRotationVelocity() +
				event.Impulse/event.second->GetInertiaMoment() * CrossProduct(event.R2, event.Collisionnormal) * 180.f/static_cast<float>(M_PI));
		
		//Objekte auseinander schieben
		float factor = event.first->GetMass() / (event.first->GetMass() + event.second->GetMass());
		
		if(DotProduct(event.Intersection, sf::Vector2f(0,-1))>0)
			event.first->AddIntersection(event.Intersection * factor, sf::Vector2f()); //FIXME
		else
			event.second->AddIntersection(-event.Intersection * (1-factor), sf::Vector2f()); //FIXME
	}
}


void sfp::CollisionManager::Friction(sfp::CollisionEvent& event)
{
	float MinFriction = std::abs(event.Impulse);
//	if(myContactManager.GetContact(event.first, event.second) != NULL && myContactManager.GetContact(event.first, event.second)->type == Contact::StaticContact)
	{
//		friction *= event.first->GetStaticFriction() * event.second->GetStaticFriction();
	}
//	else
	{
		MinFriction *= event.first->GetDynamicFriction() * event.second->GetDynamicFriction();
	}
	
	float MaxFriction = CrossProduct(event.Movement, event.Collisionnormal);
	if(!event.first->IsFixed())
	{
		MaxFriction /= 2.f/event.first->GetMass() + 1.f/event.first->GetInertiaMoment() * CrossProduct(event.R1, event.Collisionnormal);
	}
	if(!event.second->IsFixed())
	{
		MaxFriction /= 2.f/event.second->GetMass() + 1.f/event.second->GetInertiaMoment() * CrossProduct(event.R2, event.Collisionnormal);
	}
	MaxFriction = std::abs(MaxFriction);
	
	sfp::Vector2f friction(event.Collisionnormal.y, event.Collisionnormal.x);
	
	if(MinFriction > MaxFriction)
	{
//		myContactManager.SetStaticContact(first, second);
		friction *= MaxFriction;
	}
	else
	{
		friction *= MinFriction;
	}
	
	float dot = DotProduct(friction, event.Movement);
	if(dot == 0) //FIXME
	{
	}
	else if(dot < 0)
	{
		if(!event.first->IsFixed()) event.first->Impulse(event.first->ToLocal(event.Collisionpoint), -friction);
		if(!event.second->IsFixed()) event.second->Impulse(event.second->ToLocal(event.Collisionpoint), friction);
	}
	else if(dot > 0)
	{
		if(!event.first->IsFixed()) event.first->Impulse(event.first->ToLocal(event.Collisionpoint), friction);
		if(!event.second->IsFixed()) event.second->Impulse(event.second->ToLocal(event.Collisionpoint), -friction);
	}
}



void sfp::CollisionManager::OnPreciseCollision(sfp::CollisionEvent& event)
{
	
	CollisionResponse(event);
}


void sfp::CollisionManager::OnBoundingBoxCollision(sfp::CollisionEvent& event)
{

}


void sfp::CollisionManager::OnNoCollision(sfp::CollisionEvent& event)
{

}



