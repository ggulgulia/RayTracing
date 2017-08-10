#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vectors.h"
#include "ray.h"

#define pi 3.1415926535897932384626433832795

class Camera
{
    public:
        ~Camera();
        virtual Ray makeRay(Vector3D cameraOrigin) const = 0;
        
};

class PerspectiveCamera : public Camera
{

    private:
        Vector3D m_cameraOrigin; 
        Vector3D m_forward; //(normalized) forward direction of camera, from Camera Origin to image origin/point_on_image
        Vector3D m_up; //(normalized) up guide on the image
        Vector3D m_right;
        double m_width;
        double m_height;
    
    public:
        PerspectiveCamera(Vector3D cameraOrigin, Vector3D imgTarget, 
                            Vector3D upguide, const double FOV, 
                            const double aspectRatio);
        
        //this calls the constructor of ray that takes Ray object
        virtual Ray makeRay(Vector3D point) const;
        
};

#endif
