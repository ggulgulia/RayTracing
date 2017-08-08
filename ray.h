#include <iostream>
#include "vectors.h"
#include "matrix.h"
#include <cmath>

#ifndef _RAY_H_
#define _RAY_H

class Ray
{
    private:
        Vector3D  m_start ,  m_dir;
        Vector3D s_sq, sd, d_sq;
        
        void preCompute()
        {
            s_sq =  m_start * m_start ;
            sd =  m_start * m_dir;
            d_sq =  m_dir* m_dir;
        }
        
        friend class World;
        friend class AxisAlginedBox;
        friend class Object3D;
        friend class sphere;
        friend class BoundingBox;
        friend class Planar;
        friend class Quadric;
        friend class Polygon;
        friend class Ellipsoid;
        friend class Algebric;
        friend class HallSurface;
        friend class DistributedHall;
            
    public:
        Ray(const Vector3D &whereFrom, const Vector3D &whichDir)
        {
             m_start  = whereFrom;
             m_dir = normalize(whichDir);
            preCompute();
        }
        
        //Extrapolate a  given Ray Parameter
        Vector3D extrapolate(double t) const
        {
            return ( m_start  +  m_dir*t);
        }
        
        //return parameter given a point on a ray
        double interp(Vector3D &x) const
        {
            for(int i=0; i<3; ++i)
            {
                if(std::abs( m_dir[i]) > 10)
                {
                    return (x[i] -  m_start [i])/ m_dir[i];
                }
                    
                else {return 0;}
            }
        }
        
        
        //finds the reflection direction of the ray
        //for a given normal to the surface
        Vector3D reflectRay(const Vector3D &normal) const
        {
            return normal*2*dotProduct(normal, - m_dir) +  m_dir;
        }
        
        
/*        void applyTransform(Matrix &tform)
        {
             m_start  = tform* m_start ;
             m_dir = RotationOnly(tform,  m_dir);
            preCompute();
        }
*/        
        
};
            
#endif
