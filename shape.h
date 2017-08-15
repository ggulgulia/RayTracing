#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>

#include "vectors.h"
#include "ray.h"
#include "intersection.h"


//Shape is a pure virtual class
class Shape
{
public:
	virtual ~Shape() { }

	virtual bool intersect(Intersection& intersection) = 0;
	virtual bool doesIntersect(const Ray& ray) = 0;
};

/*

//TODO implement shapeSet
class ShapeSet : public Shape
{
protected:
	std::vector<Shape*> shapes;

public:
	ShapeSet();

	virtual ~ShapeSet();

	void addShape(Shape* shape);

	virtual bool intersect(Intersection& intersection);
	virtual bool doesIntersect(const Ray& ray);
};
*/
class Plane : public Shape
{
    protected:
	    Vector3D m_position;
	    Vector3D m_normal;
	    //Color m_color;

    public:
	    Plane(const Vector3D& position, const Vector3D &normal);
		      //const Color &color = Color(1.0f, 1.0f, 1.0f));

	    virtual ~Plane();
	    virtual bool intersect(Intersection &intersection);
	    virtual bool doesIntersect(const Ray &ray);
};

/***************************************************/
class Sphere : public Shape
{
    protected:
	    Vector3D m_centre;
	    double m_radius;
	    //Color m_color;

    public:
    
    //default constructor
	    Sphere(const Vector3D &m_centre, double m_radius);
		    //const Color &color = Color(1.0f, 1.0f, 1.0f));

	    virtual ~Sphere();
	    virtual bool intersect(Intersection &intersection);
	    virtual bool doesIntersect(const Ray &ray);
	    
};
/***************************************************/
#endif 
