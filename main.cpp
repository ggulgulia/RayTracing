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


void rayTrace1(Camera *camera, Shape *shape, png::image< png::rgb_pixel > &image, const double aspectRatio)
{
	
	for (size_t x = 0; x < image.get_width(); x++)
	{
		for (size_t y = 0; y < image.get_height(); y++)
		{
			Vector3D screenCoord( ((2.0*x/image.get_width())-1.0), ((2.0*y/image.get_height()) - 1.0)/aspectRatio, 0.0);
			Ray ray = camera->makeRay(screenCoord);			
			Intersection intersection(ray);
			
		    if (shape->intersect(intersection))
		    {
			
			    image[y][x] = png::rgb_pixel(23,69,46);
		    }
		    
		    else
		    {
			
			    image[y][x] = png::rgb_pixel(255,255,255);
		    }
		}
	}
	
    image.write("sphere1.png");
}
	

	 

void rayTrace2(Camera *camera, Shape *shape, png::image< png::rgb_pixel > &image, const double aspectRatio)
{
	
	for (size_t x = 0; x < image.get_width(); x++)
	{
	    double tmax{0.0}, tmin{0.0};
		for (size_t y = 0; y < image.get_height(); y++)
		{
			Vector3D screenCoord( ((2.0*x/image.get_width())-1.0), ((2.0*y/image.get_height()) - 1.0)/aspectRatio, 0.0);
			Ray ray = camera->makeRay(screenCoord);			
			Intersection intersection(ray);
			BoundingBox shapeBox = shape->getBoundingBox();
			if(shapeBox.intersect(intersection, tmin, tmax))
			{
			    tmax += 1.0;
			    tmin -= 1.0;
			    if (shape->intersect(intersection))
			    {
				
				    image[y][x] = png::rgb_pixel(255,0,0);
			    }
			    
			    else
		        {
			
			        image[y][x] = png::rgb_pixel(255,255,255);
		        }
			    
		    }
		    
		    else
		    {
			
			    image[y][x] = png::rgb_pixel(255,255,255);
		    }
		}
	}
	
	 image.write("sphere2.png");	 
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
    
std::cout << "\n*********Testing Bounding Boxes***************\n\n";

    BoundingBox testBox(Vector3D(0,0,0), Vector3D(5,5,5));
    std::cout << testBox.getMin() << " " << testBox.getMax() << "\n";
    
std::cout << "\n*********Testing Shapes***************\n\n";
    
    Vector3D centre(4,4,0);
    Sphere ball(centre, 4.0);
    
    Ray testRay2(rayOrigin, rayDir2, 4.000001);
    std::cout << ball.getBoundingBox().getMin() << " " << ball.getBoundingBox().getMax() <<"\n";
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
   
  Sphere sphere(Vector3D(0.0, 0.0, 0.0), 0.2);
  
  png::image< png::rgb_pixel > image1(width, height);
  png::image< png::rgb_pixel > image2(width, height);
  
  std::chrono::time_point<std::chrono::system_clock> start1, start2;
  std::chrono::time_point<std::chrono::system_clock> end1, end2;
 
 //testing without bounding box 
  std::cout <<"\n********************************\n";
  std::cout << "testing ray tracing without bounding box\n";
  start1 = std::chrono::system_clock::now();
  rayTrace1(&camera, &sphere, image1, aspectRatio);     
  end1 = std::chrono::system_clock::now();  
  std::chrono::duration<double> totalTime1 = end1-start1; 
  std::cout << "Elapsed time : " << totalTime1.count() << " seconds\n";
  std::cout <<"********************************\n";
  
  //testing with bounding box
  std::cout <<"\n********************************\n";
  std::cout << "testing ray tracing WITH bounding box\n";
  start2 = std::chrono::system_clock::now();
  rayTrace2(&camera, &sphere, image2, aspectRatio);     
  end2 = std::chrono::system_clock::now();
  std::chrono::duration<double> totalTime2 = end2-start2;  
  std::cout << "Elapsed time : " << totalTime2.count() << " seconds\n";
  std::cout <<"********************************\n";  
  
  double speedUp = totalTime1/totalTime2;
  std::cout << "SpeedUp: " << speedUp << "\n";
  return 0;
  
}
