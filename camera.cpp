#include <cmath>
#include "camera.h"
//#include <iostream>


//FOV is in degrees
PerspectiveCamera::PerspectiveCamera(Vector3D cameraOrigin, Vector3D imgTarget, 
                                     Vector3D upGuide, const double FOV_deg, 
                                     const double aspectRatio)
{
    double FOV_rad = pi*FOV_deg/180.00; 
    m_cameraOrigin = cameraOrigin;
    m_forward = normalize(imgTarget - cameraOrigin);
    m_right = crossProduct(m_forward, upGuide);
    m_up = normalize(crossProduct(m_right, m_forward));
    m_height = tan(FOV_rad);
    m_width = aspectRatio*m_height;
}

Ray PerspectiveCamera::makeRay(const Vector3D &cameraOrigin) const
{
    Vector3D rayDir = m_forward + (cameraOrigin.m_x*m_width*m_right) + (cameraOrigin.m_y*m_height*m_up);
    return Ray(cameraOrigin, rayDir);
}

Camera::~Camera() { }
//PerspectiveCamera::~PrespectiveCamera() { }

