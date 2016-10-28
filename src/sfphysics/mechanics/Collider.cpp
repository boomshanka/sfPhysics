#include <sfphysics/mechanics/Collider.hpp>

#include <iostream>
bool sfp::Collider::collision(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	switch (b1.bodyshape().type())
	{
	case shape_type::Circle:
		switch (b2.bodyshape().type())
		{
		case shape_type::Circle:
			// circle-circle
			return project(b1, b2, std::list<sfp::vector2f>{(b2.position() - b1.position()).normalize()});
			
		case shape_type::Polygon:
		case shape_type::Rectangle:
			// polygon-circle
			return polygonCircle(b1, b2, contact);
			
		case shape_type::Plane:
			// plane-circle
			return planeCircle(b1, b2, contact);
			
		case shape_type::Complex:
			// not implemented yet
			return false;
		}
		
			
	case shape_type::Polygon:
	case shape_type::Rectangle:
		switch (b2.bodyshape().type())
		{
		case shape_type::Circle:
			// polygon-circle
			return polygonCircle(b1, b2, contact);
			
		case shape_type::Polygon:
		case shape_type::Rectangle:
			// polygon-polygon
			return polygonPolygon(b1, b2, contact);
			
		case shape_type::Plane:
			// plane-polygon
			return planePolygon(b1, b2, contact);
			
		case shape_type::Complex:
			// not implemented yet
			return false;
		}
		
			
	case shape_type::Plane:
		switch (b2.bodyshape().type())
		{
		case shape_type::Circle:
			// plane-circle
			return planeCircle(b1, b2, contact);
			
		case shape_type::Polygon:
		case shape_type::Rectangle:
			// plane-polygon
			return planePolygon(b1, b2, contact);
			
		case shape_type::Plane:
			// plane-plane, can't collide
			return false;
			
		case shape_type::Complex:
			// not implemented yet
			return false;
		}
		
		
	case shape_type::Complex:
		// not implemented yet
		return false;
	}
}


bool sfp::Collider::planePolygon(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	
}


bool sfp::Collider::planeCircle(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	
}


bool sfp::Collider::polygonPolygon(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	// iterate above b1 separating axis
	for (unsigned int i = 0; i < b1.separatingAxisCount(); ++i)
	{
		sfp::vector2f axis = b1.separatingAxis(i);
		
		if (!(b1.project(axis)).intersects(b2.project(axis)))
		{
			return false;
		}
	}
	// separating axis from b2
	for (unsigned int i = 0; i < b2.separatingAxisCount(); ++i)
	{
		sfp::vector2f axis = b2.separatingAxis(i);
				
		if (!(b1.project(axis)).intersects(b2.project(axis)))
		{
			return false;
		}
	}
	
	// collision occured
	
	return true;
}


bool sfp::Collider::polygonCircle(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	// iterate above b1 separating axis
	for (unsigned int i = 0; i < b1.separatingAxisCount(); ++i)
	{
		sfp::vector2f axis = b1.separatingAxis(i);
		
		if (!(b1.project(axis)).intersects(b2.project(axis)))
		{
			return false;
		}
	}
	
	return true;
}


bool sfp::Collider::project(sfp::body& b1, sfp::body& b2, const std::list<sfp::vector2f>& axes) const
{
	for (sfp::vector2f axis : axes)
	{
		if (!(b1.project(axis)).intersects(b2.project(axis)))
		{
			return false;
		}
	}
	
	return true;
}


