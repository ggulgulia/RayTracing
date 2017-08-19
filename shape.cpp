#include "shape.h"
#include <cmath>

template <class T> const T& max(const T& a, const T& b)
{
    return (a>b) ? a:b;
}
template <class T> const T& min(const T& a, const T& b)
{
    return (a<b) ? a:b;
}

//------------------------------------------------------------//
//                      BoundingBox class Begins
//------------------------------------------------------------//

BoundingBox::BoundingBox()
    : m_min(Vector3D(0.0, 0.0, 0.0)),
      m_max(Vector3D(_MAX_, _MAX_, _MAX_))
{
    std::cout << "Calling default constructor of BoundingBox\n";
}

BoundingBox::BoundingBox(const Vector3D &min, const Vector3D &max)
    : m_min(min), m_max(max)
{
    std::cout << "Calling user defined constructor on bounding box\n";
}

BoundingBox::BoundingBox(const BoundingBox &boundingBox)
    : m_min(boundingBox.getMin()), m_max(boundingBox.getMax())
{
    std::cout << "CallingCopy Constructor\n";
}

BoundingBox BoundingBox::operator=(const BoundingBox &boundingBox)
{
  return BoundingBox(boundingBox.getMin(), boundingBox.getMax()); 
}

const Vector3D& BoundingBox::getMin() const
{
    return m_min;
}

const Vector3D& BoundingBox::getMax() const
{
    return m_max;
}

bool BoundingBox::intersect(Intersection& intersection, double &tmin, double &tmax)
{
  Ray localRay = intersection.getRay();
 
  //precomputation of ray parameters
  
  Vector3D rayOrigin = localRay.getOrigin();
  double rayLocX = rayOrigin.m_x;
  double rayLocY = rayOrigin.m_y;
  double rayLocZ = rayOrigin.m_z;
  
  Vector3D rayDir = localRay.getDirection();
  double rayDirX = rayDir.m_x;
  double rayDirY = rayDir.m_y;
  double rayDirZ = rayDir.m_z;
  
  double t1, t2;
  double xMin, xMax, yMin, yMax, zMin, zMax;
  
  //precomputation of box bounds
  double boxXmin = m_min.m_x;
  double boxXmax = m_max.m_x;
  double boxYmin = m_min.m_y;
  double boxYmax = m_max.m_y;
  double boxZmin = m_min.m_z;
  double boxZmax = m_max.m_z;
  
    if (abs(rayDirX) < 0.001)
    {
        if((boxXmin < rayLocX) && (boxXmax > rayLocX))
        {
            xMin = -_MAX_;
            xMax = _MAX_;
        }

        else
            return false;

    }
    
    else
    {
        t1 = (boxXmin - rayLocX)/rayDirX;
        t2 = (boxXmax - rayLocX)/rayDirY;
        
        if(t1 < t2)
        {
            xMin = t1;
            xMax = t2;
        }
        
        else
        {
            xMin = t2;
            xMax = t1;
        }
        
        if(xMax < 0.0)
            return false;
    }
    
    if(abs(rayDirY) < 0.001)
    {
        if((boxYmin < rayLocY) && (boxYmax > rayLocY))
        {
            yMin = -_MAX_;
            yMax = -_MAX_;
        }
        
        else
            return false;
    }
    
    else
    {
        t1 = (boxYmin - rayLocY)/rayDirY;
        t2 = (boxYmax - rayLocY)/rayDirY;
        
        if(t1 < t2)
        {
            yMin = t1;
            yMax = t2;
        }
        
        else
        {
            yMin = t2;
            yMax = t1;
        }
        
        if(yMax < 0.0)
            return false;
    }
    
    if(abs(rayDirZ < 0.001))
    {
        if((boxZmin < rayLocZ) && (boxZmax > rayLocZ))
        {
            zMin = -_MAX_;
            zMax = _MAX_;
        }
        
        else
            return false;
    }
    
    else
    {
        t1 = (boxZmin - rayLocZ)/rayDirZ;
        t2 = (boxZmax - rayLocZ)/rayDirZ;
        
        if(t1 < t2)
        {
            zMin = t1;
            zMax = t2;
        }
        
        else
        {
            zMin = t2;
            zMax = t1;
        }
        
        if(zMax < 0.0)
            return false;
    }
    
   tmin = max(xMin, max(yMin,zMin));
   tmax = min(xMax, min(yMax,zMax));
   
   return true;
        
}
BoundingBox::~BoundingBox() { }
//------------------------------------------------------------//
//                      BoundingBox class ENDS
//------------------------------------------------------------//


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
//                      SPHERE SHAPE BEGINS 
//------------------------------------------------------------//
/***************************************************/
//Sphere::Sphere(const Vector3D& centre, double radius, const Color& color)
Sphere::Sphere(const Vector3D& centre, double radius)
	: m_centre(centre), m_radius(radius)
{
    double xMin = centre.m_x - radius;
    double xMax = centre.m_x + radius;
    double yMin = centre.m_y - radius;
    double yMax = centre.m_y + radius;
    double zMin = centre.m_z - radius;
    double zMax = centre.m_z + radius;
    
    Vector3D minBounds(xMin, yMin, zMin);
    Vector3D maxBounds(xMax, yMax, zMax);
    
    m_bbox= BoundingBox(minBounds, maxBounds);
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Intersection& intersection)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = intersection.getRay();
	localRay.setOrigin(localRay.getOrigin() - m_centre); //implicit sphere

	// Calculate quadratic coefficients
	double a = lengthSq(localRay.getDirection());
	double b = 2 * dotProduct(localRay.getDirection(), localRay.getOrigin());
	double c = lengthSq(localRay.getOrigin()) - (m_radius*m_radius);

	// Check whether we intersect
	double discriminant = (b*b) - (4 * a * c);

    //the roots are complex and the ray doesn't intersect the sphere
	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	double t1 = (-b - std::sqrt(discriminant)) / (2*a);
	double t2 = (-b + std::sqrt(discriminant)) / (2*a);

	// First check if close intersection is valid
	if (t1 > RAY_T_MIN && t1 < intersection.getTraverse())
	{
		intersection.setTraverse(t1);
	}
	else if (t2 > RAY_T_MIN && t2 < intersection.getTraverse())
	{
		intersection.setTraverse(t2);
	}
	else
	{
		// Neither is valid
		return false;
	}

	// Finish populating intersection
	intersection.setShape(this);
	//intersection.color = color;

	return true;
}

bool Sphere::doesIntersect(const Ray& ray)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = ray;
	std::cout << localRay.getOrigin();
	localRay.setOrigin(localRay.getOrigin() - m_centre);
	std::cout << localRay.getOrigin();

	// Calculate quadratic coefficients
	double a = lengthSq(localRay.getDirection());
	double b = 2 * dotProduct(localRay.getDirection(), localRay.getOrigin());
	double c = lengthSq(localRay.getOrigin()) - (m_radius*m_radius);

	// Check whether we intersect
	double discriminant = (b*b) - 4*a*c;

	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	double t1 = (-b - std::sqrt(discriminant)) / (2*a);
	double t2 = (-b + std::sqrt(discriminant)) / (2*a);
	
	if (t1 > RAY_T_MIN && t1 < ray.getDistance())
		return true;
		
	if (t2 > RAY_T_MIN && t2 < ray.getDistance())
		return true;

	return false;
}

const BoundingBox& Sphere::getBoundingBox() const
{
    return m_bbox;
}
//------------------------------------------------------------//
//                      SPHERE SHAPE ENDS 
//------------------------------------------------------------//

//TODO: ADD MORE SHAPES

