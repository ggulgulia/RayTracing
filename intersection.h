#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "vectors.h"
#include "ray.h"

#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f

class Shape;
//class Color;

class Intersection
{
	
	private:
	    Ray m_ray;
	    double m_traverse;
	    Shape *m_pShape;
	    //Color m_color;
    
    public:
	    Intersection();
	    Intersection(const Intersection &i);
	    Intersection(const Ray &ray);

	    virtual ~Intersection();

	    Intersection& operator=(const Intersection &i);

	    bool intersected() const;
	    Vector3D position() const;
	    
	    //getter functions
	    const Shape* getShape() const;
	    const Ray getRay() const;
	    const double getTraverse() const;
	    //const Color getColor() const;
	    
	    //setter functions
	    
	    void setShape(Shape *shape);
	    void setTraverse(const double traverse);
	    void setRay(const Ray &ray);
	    //void setColor(Color color);
};

#endif
