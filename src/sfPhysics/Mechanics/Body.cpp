#include <sfPhysics/Mechanics/Body.hpp>


sfp::Body::Body(const Shape& shape, const MaterialDef& material) :
m_material(material),
m_shape(std::move(shape.copy())),
m_transformstate(transformstate::None)
{
	updateShape();
}

sfp::Body::~Body()
{

}


const sfp::MaterialDef& sfp::Body::material() const
{
	return m_material;
}

void sfp::Body::material(const sfp::MaterialDef& material)
{
	m_material = material;
	updateShape();
}


const sfp::Shape& sfp::Body::bodyshape() const
{
	return *m_shape.get();
}

void sfp::Body::bodyshape(sfp::Shape& sh)
{
	m_shape.reset();
	m_shape = std::move(sh.copy());
	updateShape();
}



const sfp::vector2f& sfp::Body::position() const
{
	return m_position;
}

void sfp::Body::position(const sfp::vector2f& pos)
{
	m_position = pos;
	m_transformstate = transformstate::None;
}


const sfp::anglef& sfp::Body::rotation() const
{
	return m_rotation;
}

void sfp::Body::rotation(const sfp::anglef& rotation)
{
	m_rotation = rotation;
	m_transformstate = transformstate::None;
}



const sfp::vector2f& sfp::Body::velocity() const
{
	return m_velocity;
}

void sfp::Body::velocity(const sfp::vector2f& vel)
{
	m_velocity = vel;
}


const sfp::anglef& sfp::Body::angularVelocity() const
{
	return m_angularVelocity;
}

void sfp::Body::angularVelocity(const anglef& vel)
{
	m_angularVelocity = vel;
}



float sfp::Body::mass() const
{
	return m_mass;
}



sfp::vector2f sfp::Body::toGlobal(const sfp::vector2f& point) const
{
	return transformation() * point;
}

sfp::vector2f sfp::Body::toLocal(const sfp::vector2f& point) const
{
	return inverseTransformation() * point;
}

const sfp::transformf& sfp::Body::transformation() const
{
	if (m_transformstate == transformstate::None)
	{
		updateTransformation();
	}
	
	return m_toGlobal;
}

const sfp::transformf& sfp::Body::inverseTransformation() const
{
	switch (m_transformstate)
	{
	case transformstate::None:
		updateTransformation();
		// no break!
		
	case transformstate::ToGlobal:
		m_toLocal = m_toGlobal.get_inverse();
		m_transformstate = transformstate::Both;
		break;
	}
	
	return m_toLocal;
}



sfp::boxf sfp::Body::bounds() const
{
	if (m_transformstate == transformstate::None)
	{
		updateTransformation();
	}
	
	return m_shape->bounds(m_toGlobal);
}


sfp::minmaxf sfp::Body::project(const sfp::vector2f& axis) const
{
	if (m_transformstate == transformstate::None)
	{
		updateTransformation();
	}
	
	return m_shape->project(axis, m_toGlobal);
}


const sfp::vector2f& sfp::Body::center() const
{
	return m_center;
}

void sfp::Body::center(const sfp::vector2f& center)
{
	m_center = center;
	m_transformstate = transformstate::None;
}



void sfp::Body::updateShape()
{
	m_mass = m_shape->area() * m_material.density();
	m_center = m_shape->center();
	m_transformstate = transformstate::None;
}


void sfp::Body::updateTransformation() const
{
	m_toGlobal.clear();
	m_toGlobal.translate(m_position).rotate(m_rotation).translate(-m_center);
	m_transformstate = transformstate::ToGlobal;
}



