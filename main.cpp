#include <iostream>
#include <chrono>
#include "vectors.h"
#include "matrix.h"
#include "intersection.h"
#include "ray.h"
#include "shape.h"
#include "camera.h"
#include "image.h"
#include <cmath>
#include <stdlib.h>
#include <png++/png.hpp>


void rayTrace(Camera *camera, Shape *shape, png::image< png::rgb_pixel > &image, const double aspectRatio)
{
	
	for (size_t x = 0; x < image.get_width(); x++)
	{
	    //double tmax{0.0}, tmin{0.0};
		for (size_t y = 0; y < image.get_height(); y++)
		{
			Vector3D screenCoord( ((2.0*x/image.get_width())-1.0), ((2.0*y/image.get_height()) - 1.0)/aspectRatio, 0.0);
			Ray ray = camera->makeRay(screenCoord);			
			Intersection intersection(ray);
			//BoundingBox shapeBox
			//if(shape->getBoundingBox().intersect
			if (shape->intersect(intersection))
			{
				
				image[y][x] = png::rgb_pixel(23,69,46);
			}
			else
			{
				
				image[y][x] = png::rgb_pixel(25,255,255);
			}
		}
	}
	
	 image.write("sphere.png");
	 
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
  
  std::cout << "\n*********Testing Images***************\n\n";
  
  size_t width = strtoul(argv[1], NULL, 0);
  size_t height = strtoul(argv[2], NULL, 0);

  Vector3D cameraOrigin(-5.0, 1.0, 0.0);
  Vector3D imgLoc(0.0, 1.0, 0.0);
  Vector3D upGuide(0.0, 1.0, 0.0);
  double fov = 89.0;
  double aspectRatio = (double)width/(double)height;
  std::cout << "aspect ratio : " << aspectRatio << "\n";
  
  PerspectiveCamera camera(cameraOrigin,
		                   imgLoc,  
		                   upGuide, fov,
                           aspectRatio);
   
  Sphere sphere(Vector3D(0.0, 0.0, 0.0), 0.5);
  
  png::image< png::rgb_pixel > image(width, height);
  
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> end;
  
  start = std::chrono::system_clock::now();
  rayTrace(&camera, &sphere, image, aspectRatio);     
  end = std::chrono::system_clock::now();
  
  std::chrono::duration<double> totalTime = end-start;
  
  std::cout << "Elapsed time : " << totalTime.count() << " seconds\n";
  return 0;
}
