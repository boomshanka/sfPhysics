#include <sfPhysics/Mechanics/Collider.hpp>


#include<iostream>

template<typename T>
T square(T base)
{
	return base*base;
}


bool sfp::Collider::collision(sfp::Body& b1, sfp::Body& b2, sfp::Contact& contact)
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


bool sfp::Collider::planePolygon(sfp::Body& b1, sfp::Body& b2, sfp::Contact& contact)
{
	// Only one separating axis is required, the normal of the plane
	vector2f axis = planeNormal(b1);
	
	// Only check polygon minimum < projection of plane center point
	// since projection axis is the normal of the plane the projection of the center is always on the positive end
	if (b2.project(axis).min() <= dot_product(axis, b1.position()))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}

// TODO: Collision check is the same as planePolygon
bool sfp::Collider::planeCircle(sfp::Body& b1, sfp::Body& b2, sfp::Contact& contact)
{
	// Only one separating axis is required, the normal of the plane
	const PlaneShape& plane = dynamic_cast<const PlaneShape&>(b1.bodyshape());
	vector2f axis = plane.normal(b1.transformation());
	
	// Only check circle minimum < projection of plane center point
	// since projection axis is the normal of the plane the projection of the center is always on the positive end
	if (b2.project(axis).min() <= dot_product(axis, b1.toGlobal(plane.center())))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}


bool sfp::Collider::polygonPolygon(sfp::Body& b1, sfp::Body& b2, sfp::Contact& contact)
{
	// Fill list with all separating axis
	m_axes.clear();
	findPolygonSeparatingAxes(b1);
	findPolygonSeparatingAxes(b2);
	
	// Check for collision
	if (project(b1, b2, m_axes))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}


bool sfp::Collider::polygonCircle(sfp::Body& b1, sfp::Body& b2, sfp::Contact& contact)
{
	sfp::vector2f closestPoint = closestPolygonPoint(b1, b2.position());
	
	// Check length from closest point to circle center
	if ((closestPoint - b2.position()).squaredLength() <= square<float>(circleRadius(b2)))
	{
		// Collision! Compute contact points
		
		
		return true;
	}
	
	return false;
}


bool sfp::Collider::circleCircle(sfp::Body& b1, sfp::Body& b2, sfp::Contact& contact)
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
	m_radius = shape.radius();
}

void sfp::Collider::dispatch(const sfp::PolygonShape& shape)
{
	if (shape.pointCount() > 2)
	{
		switch (m_polygonTask)
		{
		case PolygonTask::closestPoint:
			m_point = closestPolygonPoint(m_point, shape.pointCount(), [&](unsigned int i){return m_transform.transform(shape.point(i));} );
			break;
			
		case PolygonTask::separatingAxis:
			for (unsigned int i = 1; i < shape.pointCount(); ++i)
			{
				m_axes.push_back((m_transform.transform(shape.point(i))-m_transform.transform(shape.point(i-1))).normal());
			}
			m_axes.push_back((m_transform.transform(shape.point(0))-m_transform.transform(shape.point(shape.pointCount()))).normal());
			break;
		}
	}
}

void sfp::Collider::dispatch(const sfp::RectangleShape& shape)
{
	switch (m_polygonTask)
	{
	case PolygonTask::closestPoint:
		m_point = closestPolygonPoint(m_point, 4, [&](unsigned int i){return m_transform.transform(shape.corner(i));} );
		break;
		
	case PolygonTask::separatingAxis:
		// Add the two separating axis
		m_axes.push_back(m_transform.transform(shape.corner(0))-m_transform.transform(shape.corner(1)));
		m_axes.push_back(m_transform.transform(shape.corner(1))-m_transform.transform(shape.corner(2)));
		break;
	}
}

void sfp::Collider::dispatch(const sfp::PlaneShape& shape)
{
	// request for normal
	m_normal = shape.normal(m_transform);
}


bool sfp::Collider::project(sfp::Body& b1, sfp::Body& b2, const std::list<sfp::vector2f>& axes)
{
	// Loop over all axes
	for (sfp::vector2f axis : axes)
	{
		// Check if projection of both bodys overlap
		if (!(b1.project(axis)).intersects(b2.project(axis)))
		{
			// No overlap -> no collision, exit
			return false;
		}
	}
	
	// Projections for all axes overlap -> collision
	return true;
}


sfp::vector2f sfp::Collider::closestPolygonPoint(sfp::Body& polygon, const sfp::vector2f& reference)
{
	// Use visitor pattern to find closest point to reference
	m_polygonTask = PolygonTask::closestPoint;
	m_point = reference;
	m_transform = polygon.transformation();
	polygon.bodyshape().accept(*this);
	
	return m_point;
}


void sfp::Collider::findPolygonSeparatingAxes(sfp::Body& polygon)
{
	// Use visitor pattern to find separating axes
	m_polygonTask = PolygonTask::separatingAxis;
	m_transform = polygon.transformation();
	polygon.bodyshape().accept(*this);
}


float sfp::Collider::circleRadius(sfp::Body& circle)
{
	circle.bodyshape().accept(*this);
	return m_radius;
}


sfp::vector2f sfp::Collider::planeNormal(sfp::Body& plane)
{
	m_transform = plane.transformation();
	plane.bodyshape().accept(*this);
	return m_normal;
}


template <typename F>
sfp::vector2f sfp::Collider::closestPolygonPoint(sfp::vector2f referencePoint, unsigned int pointCount, F globalPointPosition)
{
	// Find closest corner, start with corner(0)
	unsigned int closestPointNumber = 0;
	float minDistance = (globalPointPosition(closestPointNumber) - referencePoint).squaredLength();
	
	for (unsigned int i = 1; i < pointCount; ++i)
	{
		float currentDistance = vector2f(globalPointPosition(i) - referencePoint).squaredLength();
		
		if (currentDistance < minDistance)
		{
			closestPointNumber = i;
			minDistance = currentDistance;
		}
	}
	
	vector2f previousCorner = globalPointPosition((closestPointNumber == 0) ? (pointCount-1) : closestPointNumber-1);
	vector2f currentCorner = globalPointPosition(closestPointNumber);
	vector2f nextCorner = globalPointPosition((closestPointNumber+1) % pointCount);
	
	// Check if closest point is inbetween two corners
	if (dot_product(currentCorner-previousCorner, referencePoint-currentCorner) < 0) // closest corner to previous corner
	{
		// Inbetween closest and previous corner
		vector2f axis = (previousCorner-currentCorner).normalize();
		return currentCorner + dot_product(referencePoint-currentCorner, axis) * axis;
	}
	else if (dot_product(currentCorner-nextCorner, referencePoint-currentCorner) < 0) // closest corner to next corner
	{
		// Inbetween closest and next corner
		vector2f axis = (nextCorner-currentCorner).normalize();
		return currentCorner + dot_product(referencePoint-currentCorner, axis) * axis;
	}
			
	// else corner is closest point
	return currentCorner;
}
