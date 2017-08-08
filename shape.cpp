#include "shape.h"


/*
ShapeSet::ShapeSet()
{
}

ShapeSet::~ShapeSet()
{
}

void ShapeSet::addShape(Shape* shape)
{
	shapes.push_back(shape);
}

bool ShapeSet::intersect(Intersection& intersection)
{
	bool doesIntersect = false;
    
    std::vector<Shape*>::iterator iter;
	for (iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		Shape *curShape = *iter;
		if (curShape->intersect(intersection))
			doesIntersect = true;
	}

	return doesIntersect;
}

bool ShapeSet::doesIntersect(const Ray& ray)
{
    std::vector<Shape*>::iterator iter;
	
	for (iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		Shape *curShape = *iter;
		if (curShape->doesIntersect(ray))
			return true;
	}

	return false;
}
*/

//------------------------------------------------------------//
//                      PLANE Shape
//------------------------------------------------------------//
//user defined constructor for plane
//Plane::Plane(const Vector3D& position, const Vector3D& normal, const Color& color)
Plane::Plane(const Vector3D& position, const Vector3D& normal)
	: m_position(position), m_normal(normal)
{
    std::cout << "calling deafault constructor on Plane object\n";
}

Plane::~Plane()
{
}

bool Plane::intersect(Intersection &intersection)
{
	// First, check if we intersect
	double dDotN = dotProduct(intersection.getRay().getDirection(), m_normal);

	if (dDotN == 0.0f)
	{
		// We just assume the ray is not embedded in the plane
		return false;
	}

	// Find point of intersection
	double t = (dotProduct(m_position - intersection.getRay().getOrigin(), m_normal)/ dDotN);

	if (t <= RAY_T_MIN || t >= intersection.getTraverse())
	{
		// Outside relevant range
		return false;
	}

	intersection.setTraverse(t);
	intersection.setShape(this);
	//intersection.setColor(color);

	return true;
}

bool Plane::doesIntersect(const Ray& ray)
{
	std::cout << "executing doesIntersect() \n";
	
	// First, check if we intersect
	double dDotN = dotProduct(ray.getDirection(), m_normal);

	if (dDotN == 0.0f)
	{
		//return if ray and plane normal are orthogonal
		return false;
	}

	// 
	double t = dotProduct(m_position - ray.getOrigin(), m_normal) / dDotN;

	if (t <= RAY_T_MIN || t >= ray.getDistance())
	{
		// Outside relevant range
		return false;
	}

	return true;
}
//------------------------------------------------------------//
//                      PLANE SHAPE ENDS
//------------------------------------------------------------//


//------------------------------------------------------------//
//                      SPHERE SHAPE BEGINS 
//------------------------------------------------------------//
/***************************************************
//Sphere::Sphere(const Vector3D& centre, double radius, const Color& color)
Sphere::Sphere(const Vector3D& centre, double radius)
	: m_centre(centre), m_radius(radius)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Intersection& intersection)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = intersection.ray;
	localRay.origin -= centre;

	// Calculate quadratic coefficients
	double a = localRay.direction.length2();
	double b = 2 * dot(localRay.direction, localRay.origin);
	double c = localRay.origin.length2() - sqr(radius);

	// Check whether we intersect
	double discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

	// First check if close intersection is valid
	if (t1 > RAY_T_MIN && t1 < intersection.t)
	{
		intersection.t = t1;
	}
	else if (t2 > RAY_T_MIN && t2 < intersection.t)
	{
		intersection.t = t2;
	}
	else
	{
		// Neither is valid
		return false;
	}

	// Finish populating intersection
	intersection.pShape = this;
	intersection.color = color;

	return true;
}

bool Sphere::doesIntersect(const Ray& ray)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = ray;
	localRay.origin -= centre;

	// Calculate quadratic coefficients
	double a = localRay.direction.length2();
	double b = 2 * dot(localRay.direction, localRay.origin);
	double c = localRay.origin.length2() - sqr(radius);

	// Check whether we intersect
	double discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	if (t1 > RAY_T_MIN && t1 < ray.tMax)
		return true;

	double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	if (t2 > RAY_T_MIN && t2 < ray.tMax)
		return true;

	return false;
}
***************************************************/
//------------------------------------------------------------//
//                      SPHERE SHAPE ENDS 
//------------------------------------------------------------//

//TODO: ADD MORE SHAPES
