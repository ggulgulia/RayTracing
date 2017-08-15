#include "ray.h"
#include <ostream>

//default constructor making the ray start at m_origin 
Ray::Ray()
	: m_origin(0.0f, 0.0f, 0.0f), m_direction(), m_distance(RAY_T_MAX)
{
    std::cout << "calling default constructor on Ray objcet\n";
}

//copy construtor
Ray::Ray(const Ray& ray)
	: m_origin(ray.m_origin), m_direction(ray.m_direction), m_distance(ray.m_distance)
{
    std::cout << "calling copy constructor on Ray objcet\n";
}

//user defined constructor
Ray::Ray(const Vector3D& origin, const Vector3D& direction, double distance)
	: m_origin(origin), m_distance(distance)
{
    std::cout << "calling user defined constructor on Ray objcet\n";
    m_direction = normalize(direction);
}

//destructor
Ray::~Ray()
{
}

//assignment operator
Ray& Ray::operator =(const Ray& ray)
{
	this->m_origin = ray.m_origin;
	this->m_direction = ray.m_direction;
	this->m_distance = ray.m_distance;
	return *this;
}

std::ostream& operator<<(std::ostream &out, const Ray &ray)
{
    out << "Origin: " << ray.getOrigin() << "\n";
    out << "Direction: " << ray.getDirection() << "\n";
    out << "Distance: " << ray.getDistance() << "\n";
    
    return out;
}

//caclulates the point on the ray at a given distance from its origin
Vector3D Ray::calculate(double distance) const
{
	return (this->m_origin + (this->m_direction * distance));
}

//getter functions

const Vector3D Ray::getDirection() const
{
 return m_direction;
}
const Vector3D  Ray::getOrigin() const
{
    return m_origin;
}
const double Ray::getDistance() const
{
    return m_distance;
}

/****************setter functions*******************/
void Ray::setOrigin(const Vector3D &origin)
{
    this->m_origin = origin;
}

//direction has to be normalized
void Ray::setDirection(const Vector3D &direction)
{
    this->m_direction = normalize(direction);
}

void Ray::setDistance(double distance)
{
    this->m_distance = distance;
}


