#include <sfphysics/mechanics/body.hpp>


sfp::body::body(const Shape& shape, const materialdef& material) :
m_material(material),
m_shape(std::move(shape.copy())),
m_transformstate(transformstate::None)
{
	update_shape();
}

sfp::body::~body()
{

}


const sfp::materialdef& sfp::body::material() const
{
	return m_material;
}

void sfp::body::material(const sfp::materialdef& material)
{
	m_material = material;
	update_shape();
}


const sfp::Shape& sfp::body::bodyshape() const
{
	return *m_shape.get();
}

void sfp::body::bodyshape(sfp::Shape& sh)
{
	m_shape.reset();
	m_shape = std::move(sh.copy());
	update_shape();
}



const sfp::vector2f& sfp::body::position() const
{
	return m_position;
}

void sfp::body::position(const sfp::vector2f& pos)
{
	m_position = pos;
	m_transformstate = transformstate::None;
}


const sfp::anglef& sfp::body::rotation() const
{
	return m_rotation;
}

void sfp::body::rotation(const sfp::anglef& rotation)
{
	m_rotation = rotation;
	m_transformstate = transformstate::None;
}



const sfp::vector2f& sfp::body::velocity() const
{
	return m_velocity;
}

void sfp::body::velocity(const sfp::vector2f& vel)
{
	m_velocity = vel;
}


const sfp::anglef& sfp::body::angular_velocity() const
{
	return m_angular_velocity;
}

void sfp::body::angular_velocity(const anglef& ang_vel)
{
	m_angular_velocity = ang_vel;
}



float sfp::body::mass() const
{
	return m_mass;
}



sfp::vector2f sfp::body::to_global(const sfp::vector2f& point) const
{
	return get_transformation() * point;
}

sfp::vector2f sfp::body::to_local(const sfp::vector2f& point) const
{
	return get_inverse_transformation() * point;
}

const sfp::transformf& sfp::body::get_transformation() const
{
	if (m_transformstate == transformstate::None)
	{
		update_transformation();
	}
	
	return m_to_global;
}

const sfp::transformf& sfp::body::get_inverse_transformation() const
{
	switch (m_transformstate)
	{
	case transformstate::None:
		update_transformation();
		// no break!
		
	case transformstate::ToGlobal:
		m_to_local = m_to_global.get_inverse();
		m_transformstate = transformstate::Both;
		break;
	}
	
	return m_to_local;
}



sfp::boxf sfp::body::bounds() const
{
	if (m_transformstate == transformstate::None)
	{
		update_transformation();
	}
	
	return m_shape->bounds(m_to_global);
}


sfp::minmaxf sfp::body::project(const sfp::vector2f& axis) const
{
	if (m_transformstate == transformstate::None)
	{
		update_transformation();
	}
	
	return m_shape->project(axis, m_to_global);
}


const sfp::vector2f& sfp::body::center() const
{
	return m_center;
}

void sfp::body::center(const sfp::vector2f& center)
{
	m_center = center;
	m_transformstate = transformstate::None;
}



void sfp::body::update_shape()
{
	m_mass = m_shape->area() * m_material.density();
	m_center = m_shape->center();
	m_transformstate = transformstate::None;
}


void sfp::body::update_transformation() const
{
	m_to_global.clear();
	m_to_global.translate(m_position).rotate(m_rotation).translate(-m_center);
	m_transformstate = transformstate::ToGlobal;
}



