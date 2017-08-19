#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>

#include "vectors.h"
#include "ray.h"
#include "intersection.h"

#define _MAX_ 100000000
#define INF   10000000000000

template <class T> const T& max(const T& a, const T& b);
template <class T> const T& min(const T& a, const T& b);


//Shape is a pure virtual class
class BoundingBox ;

class Shape
{
public:
	virtual ~Shape() { }

	virtual bool intersect(Intersection& intersection) = 0;
	virtual bool doesIntersect(const Ray& ray) = 0;
	virtual const BoundingBox& getBoundingBox() const = 0;
};

class BoundingBox 
{
    private:
        Vector3D m_min;
        Vector3D m_max;
    
    public:
        BoundingBox();
        BoundingBox(const Vector3D &min, const Vector3D &max);
        BoundingBox(const BoundingBox &boundingBox);
        ~BoundingBox();
        
         bool intersect(Intersection& intersection, double &tmin, double &tmax);
         
         BoundingBox operator=(const BoundingBox &boundingBox);
         const Vector3D& getMin() const;
         const Vector3D& getMax() const;
        //virtual bool doesIntersect(const Ray& ray)
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


***************************************************/
class Sphere : public Shape
{
    protected:
	    Vector3D m_centre;
	    double m_radius;
	    BoundingBox m_bbox;
	    //Color m_color;

    public:
    
    //default constructor
	    Sphere(const Vector3D &m_centre, double m_radius);
		    //const Color &color = Color(1.0f, 1.0f, 1.0f));

	    virtual ~Sphere();
	    virtual bool intersect(Intersection &intersection);
	    virtual bool doesIntersect(const Ray &ray);
	    virtual const BoundingBox& getBoundingBox() const;
	    
};
/***************************************************/


#endif 
