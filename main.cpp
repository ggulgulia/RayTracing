#include <iostream>
#include "vectors.h"
#include "matrix.h"
#include "intersection.h"
#include "ray.h"
#include "shape.h"
#include "camera.h"
#include "image.h"
#include <cmath>
#include <iomanip>

void rayTrace(Image& image, Camera* camera, Plane plane)
{
	// Do nothing
	for (size_t x = 0; x < image.getWidth(); x++)
	{
		for (size_t y = 0; y < image.getHeight(); y++)
		{
			Vector3D screenCoord((2.0f*x) / image.getWidth() - 1.0f, (-2.0f*y) / image.getHeight() + 1.0f, 0.0);
			Ray ray = camera->makeRay(screenCoord);

			double* curPixel = image.getPixel(x, y);

			Intersection intersection(ray);
			if (plane.intersect(intersection))
			{
				*curPixel = 256;
			}
			else
			{
				*curPixel = 0;
			}
		}
	}
}

int main(int argc, char** argv)
{

    std::cout << "*********Testing Vectors***************\n\n";
    
    Vector3D a, point(2,2, 4), normal(0, 0, 1), rayOrigin(4,-4,0), rayDir(0, 0, 1), rayDir2(0,1,0);
    
        //Vector3D rand1(0.2785, 0.5469, 0.9575), rand2(0.9649, 0.1576, 0.9706);
    
    //std::cout << "Cross Product of : " << rand1 << " and " << rand2 << " = " << crossProduct(rand1, rand2) << "\n";
    
    //std::cout << "test1: " << dotProduct(rand1, crossProduct(rand1, rand2)) << "\n";
    Matrix m_sample;
    
    std::cout << "\n*********End of Testing Vectors***************\n\n";


    
    std::cout << "*********Testing Rays***************\n\n";
    
    Ray myRay, testRay(rayOrigin, rayDir, 13);   
    std::cout << testRay.calculate(2);
    
    std::cout << "\n*********End of Testing Rays***************\n\n";


    
    std::cout << "*********Testing Intersection***************\n\n";
    
    Intersection inter(testRay);
    std::cout << "\n" << testRay.getOrigin() << "\n" << testRay.getDistance() <<"\n" << testRay.getDirection() << "\n\n";
  
    std::cout << inter.getRay() << "\n" << inter.getShape() << "\n" << "traverse " << inter.getTraverse() << "\n";
    
    std::cout << "*********End of Testing Intersections***************\n\n";
    
    
     std::cout << "\n*********Testing Shapes***************\n\n";
    Plane xyPlane(point, normal);
    
    if(xyPlane.doesIntersect(testRay))
    {
        std::cout << "the ray intersects the plane\n";
    }
    
    
    Vector3D centre(4,4,0);
    Sphere ball(centre, 4.0);
    
    Ray testRay2(rayOrigin, rayDir2, 4.000001);
    std::cout << "\nRay direction: " << rayDir2 << "\n";
//rayDir2(12,23,19)    
//rayOrigin(2,-4,0)
    std::cout << testRay2.getDirection().isNormalized() <<"\n";
    
    if(ball.doesIntersect(testRay2))
    {
        std::cout << "the ray intersects the ball\n";
    }
    
    else
    {
        std::cout << "ray doesn't intersect the ball\n";
    }
    
    
    
  std::cout << "\n*********End of Testing Shapes***************\n\n";   
    
    return 0;
}
