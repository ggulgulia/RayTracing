#include <iostream>
#include "vectors.h"
#include "matrix.h"
#include "intersection.h"
#include "ray.h"
#include <cmath>
#include <iomanip>

int main(int argc, char** argv)
{

    Vector3D a, b(2,1, 4), c(0, -1, 3), o(5,9,2), dir(1,1,0);
    Matrix m_sample;
    
    Ray myRay, anotherRay(o, dir, 1);
    
    std::cout << "all working okay till now\n";
    
    std::cout << anotherRay.calculate(2);
    
    Intersection intersectionObj(anotherRay);
    
  //  std::cout << "\n" << anotherRay.getOrigin() << "\n" << anotherRay.getDistance() <<"\n" << anotherRay.getDirection() << "\n";
    
    return 0;
}
