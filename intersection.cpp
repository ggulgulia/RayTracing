#include "intersection.h"

//default constructor
Intersection::Intersection()
	: m_ray(), m_t(RAY_T_MAX), m_pShape(NULL)
{
}

//copy constructor
Intersection::Intersection(const Intersection &i)
	: m_ray(i.m_ray), m_t(i.m_t), m_pShape(i.m_pShape)
{
}

//user defined constructor withot any shape object
Intersection::Intersection(const Ray &ray)
	: m_ray(ray), m_t(ray.getDistance()), m_pShape(NULL)
{
}

Intersection::~Intersection()
{
}

//overloaded assignment operator
Intersection& Intersection::operator =(const Intersection &i)
{
	this->m_ray = i.m_ray;
	this->m_t = i.m_t;
	this->m_pShape = i.m_pShape;
	return *this;
}

//member function to check if there's any intersection  
bool Intersection::intersected() const
{
	return (m_pShape != NULL);
}

Vector3D Intersection::position() const
{
	return m_ray.calculate(m_t);
}
