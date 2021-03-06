#ifndef RAY_H
#define RAY_H

#include "vectors.h"

// In order to prevent bouncing rays self-intersecting
#define RAY_T_MIN 0.0001f

// 'Infinite' distance, used as a default value
#define RAY_T_MAX 1.0e30f

class Ray
{
    private:
	    Vector3D m_origin; // start
	    Vector3D m_direction; //direction of ray traversal, has to be normalized
	    double m_distance; //how much distance a ray travels before it comes to stop
	                       //funny but practical definition
    
    public:
	    Ray();
	    Ray(const Ray &ray);	    
	    Ray(const Vector3D &origin, 
            const Vector3D &direction, 
            double distance = RAY_T_MAX);

	    virtual ~Ray();

	    Ray& operator =(const Ray &ray);
	    friend std::ostream& operator<<(std::ostream &out, const Ray &ray);

	    //returns the coordinates (in vector form) on the ray 
	    //at a distance 'distance' on the ray (along the ray direction)
	    Vector3D calculate(double distance) const;
	    
	    //getter functions
	    const Vector3D getDirection() const;
	    const Vector3D getOrigin() const;
	    const double getDistance() const;
	    
	    //setter functions
	    void setOrigin(const Vector3D &origin);
	    void setDirection(const Vector3D &direction); //direction has to be normalized
	    void setDistance(double distance);

};
            
#endif
