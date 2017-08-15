#include "intersection.h"

//default constructor
Intersection::Intersection()
	: m_ray(), m_traverse(RAY_T_MAX), m_pShape(NULL)
{
}

//copy constructor
Intersection::Intersection(const Intersection &i)
	: m_ray(i.m_ray), m_traverse(i.m_traverse), m_pShape(i.m_pShape)
{
}

//user defined constructor without any shape object, 
//makes the intersect object traverse a distance equal to ray travesal distance
Intersection::Intersection(const Ray &ray)
	: m_ray(ray), m_traverse(ray.getDistance()), m_pShape(NULL)
{
    std::cout << "Calling Intersection constructor taking Ray object\n";
}

Intersection::~Intersection()
{
}

//overloaded assignment operator
Intersection& Intersection::operator =(const Intersection &i)
{
	this->m_ray = i.m_ray;
	this->m_traverse = i.m_traverse;
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
	return m_ray.calculate(m_traverse);
}


//getter functions
const Shape* Intersection::getShape() const
{
    return m_pShape;
}
const Ray Intersection::getRay() const
{
    return m_ray;
}

const double Intersection::getTraverse() const
{
    return m_traverse;
}
/*
const Color Intersection::getColor() const
{
    return m_color;
}*/

//setter functions

void Intersection::setShape(Shape *shape)
{
    m_pShape = shape;
}

void Intersection::setTraverse(const double traverse)
{
    m_traverse = traverse;
}

void Intersection::setRay(const Ray &ray)
{
    m_ray = ray;
}

//void setColor(Color color);
