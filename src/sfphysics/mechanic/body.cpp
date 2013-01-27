#include <sfphysics/mechanic/body>



sfp::body::body()
{

}

sfp::body::~body()
{

}



void sfp::body::add_form(std::shared_ptr<sfp::form> add)
{

}

bool sfp::body::remove_form(std::shared_ptr<sfp::form> remove)
{

}

void sfp::body::clear_forms()
{

}



const sfp::vector2f& sfp::body::position() const
{
	return m_position;
}

void sfp::body::position(const vector2f& position)
{
	m_position = position;
}

			
const sfp::anglef& sfp::body::rotation() const
{
	return m_rotation;
}

void sfp::body::rotation(const anglef& rotation)
{
	m_rotation = rotation;
}



const sfp::vector2f& sfp::body::velocity()
{
	return m_velocity;
}

void sfp::body::velocity(const sfp::vector2f& vel)
{
	m_velocity = vel;
}

void sfp::body::add_velocity(const sfp::vector2f& vel)
{
	m_velocity += vel;
}


const sfp::anglef& sfp::body::rotation_velocity()
{
	return m_rotation_velocity;
}

void sfp::body::rotation_velocity(const sfp::anglef& rot)
{
	m_rotation_velocity = rot;
}

void sfp::body::add_rotation_velocity(const sfp::anglef& rot)
{
	m_rotation_velocity += rot;
}



sfp::vector2f sfp::body::to_global(const sfp::vector2f& local) const
{
	sfp::vector2f global(local - m_center);
	global.rotate(m_rotation);
	
	return global + m_position;
}

sfp::vector2f sfp::body::to_local(const sfp::vector2f& global) const
{
	sfp::vector2f local(global - m_position);
	local.rotate(-m_rotation);
	
	return local + m_center;
}


