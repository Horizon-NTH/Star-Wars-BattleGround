#include "Object.h"

Object::Object(std::string name) :
	m_name(name)
{
}

Object::~Object()
{
}

std::string Object::get_name()
{
	return m_name;
}

std::ostream& operator<<(std::ostream& os, const Object& object)
{
	object.stat(os);
	return os;
}
