#include <sfphysics/mechanics/Collider.hpp>


bool sfp::Collider::collision(sfp::body& b1, sfp::body& b2, sfp::Contact& contact)
{
	switch (b1.bodyshape().type())
	{
	case shape_type::Circle:
		switch (b2.bodyshape().type())
		{
		case shape_type::Circle:
			// circle-circle
			return circleCircle(b1, b2, contact);
			
		case shape_type::Polygon:
		case shape_type::Rectangle:
			// polygon-circle
			return polygonCircle(b2, b1, contact);
			
		case shape_type::Plane:
			// plane-circle
			return planeCircle(b2, b1, contact);
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
			return planePolygon(b2, b1, contact);
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
		}
	}
}


bool sfp::Collider::planePolygon(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	// Only one separating axis is required, the normal of the plane
	const sfp::PlaneShape& plane = dynamic_cast<const PlaneShape&>(b1.bodyshape());
	sfp::vector2f axis = plane.normal(b1.get_transformation());
	
	// Only check polygon minimum < projection of plane center point
	// since projection axis is the normal of the plane the projection of the center is always on the positive end
	if (b2.project(axis).min() <= dot_product(axis, b1.to_global(plane.center())))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}

// TODO: Collision check is the same as planePolygon
bool sfp::Collider::planeCircle(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	// Only one separating axis is required, the normal of the plane
	const sfp::PlaneShape& plane = dynamic_cast<const PlaneShape&>(b1.bodyshape());
	sfp::vector2f axis = plane.normal(b1.get_transformation());
	
	// Only check circle minimum < projection of plane center point
	// since projection axis is the normal of the plane the projection of the center is always on the positive end
	if (b2.project(axis).min() <= dot_product(axis, b1.to_global(plane.center())))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}


bool sfp::Collider::polygonPolygon(sfp::body& b1, sfp::body& b2, sfp::Contact& contact)
{
	// Fill list with all separating axis
	m_axes.clear();
	m_nearestPoint = false;
	m_transform = b1.get_transformation();
	b1.bodyshape().accept(*this);
	m_transform = b2.get_transformation();
	b2.bodyshape().accept(*this);
	
	// Check for collision
	if (project(b1, b2, m_axes))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}


bool sfp::Collider::polygonCircle(sfp::body& b1, sfp::body& b2, sfp::Contact& contact)
{
	// Find the closest point of the polygon to the circle
	m_nearestPoint = true;
	m_point = b2.position();
	m_transform = b1.get_transformation();
	b1.bodyshape().accept(*this);
		
	// Check for collision with the axis from the found point to the circle center
	if (project(b1, b2, std::list<sfp::vector2f>{(b2.position()-m_point).normalize()}))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}


bool sfp::Collider::circleCircle(sfp::body& b1, sfp::body& b2, sfp::Contact& contact) const
{
	if (project(b1, b2, std::list<sfp::vector2f>{(b2.position() - b1.position()).normalize()}))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}


void sfp::Collider::dispatch(const sfp::CircleShape& shape)
{

}

void sfp::Collider::dispatch(const sfp::PolygonShape& shape)
{
	if (shape.point_count() > 2)
	{
		if (m_nearestPoint)
		{
			vector2f center = m_point;
			m_point = m_transform.transform(shape.point(0));
			float distance = vector2f(m_point - center).squaredLength();
			for (unsigned int i = 1; i < shape.point_count(); ++i)
			{
				vector2f temp = m_transform.transform(shape.point(i));
				if ((temp-center).squaredLength() < distance)
				{
					distance = (temp-center).squaredLength();
					m_point = temp;
				}
			}
		}
		else
		{
			for (unsigned int i = 1; i < shape.point_count(); ++i)
			{
				m_axes.push_back((m_transform.transform(shape.point(i))-m_transform.transform(shape.point(i-1))).normal());
			}
			
			m_axes.push_back((m_transform.transform(shape.point(0))-m_transform.transform(shape.point(shape.point_count()))).normal());
		}
	}
}

void sfp::Collider::dispatch(const sfp::RectangleShape& shape)
{
	if (m_nearestPoint)
	{
		vector2f center = m_point;
		m_point = m_transform.transform(shape.corner(0));
		float distance = vector2f(m_point - center).squaredLength();
		for (unsigned int i = 1; i < 4; ++i)
		{
			vector2f temp = m_transform.transform(shape.corner(i));
			if ((temp-center).squaredLength() < distance)
			{
				distance = (temp-center).squaredLength();
				m_point = temp;
			}
		}
	}
	else
	{
		m_axes.push_back(m_transform.transform(shape.corner(0))-m_transform.transform(shape.corner(1)));
		m_axes.push_back(m_transform.transform(shape.corner(1))-m_transform.transform(shape.corner(2)));
	}
}

void sfp::Collider::dispatch(const sfp::PlaneShape& shape)
{
	
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
