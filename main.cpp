#include <iostream>
#include "vectors.h"
#include "matrix.h"
#include "intersection.h"
#include "ray.h"
#include "shape.h"
#include <cmath>
#include <iomanip>

int main(int argc, char** argv)
{

    Vector3D a, point(2,2, 4), normal(0, 0, 1), rayOrigin(2,2,-8), rayDir(0, 0, 1);
    Matrix m_sample;
    
    Ray myRay, testRay(rayOrigin, rayDir, 13);
    
    std::cout << "all working okay till now\n";
    
    std::cout << testRay.calculate(2);
    
    Intersection inter(testRay);
    
    std::cout << "\n" << testRay.getOrigin() << "\n" << testRay.getDistance() <<"\n" << testRay.getDirection() << "\n";
  
    std::cout << inter.getRay() << "\n" << inter.getShape() << "\n" << "traverse" << inter.getTraverse() << "\n";

    Plane xyPlane(point, normal);
    
    if(xyPlane.doesIntersect(testRay))
    {
        std::cout << "the ray intersects the plane\n";
    }
    
    return 0;
}
