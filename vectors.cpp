#include <cstdlib>
#include <iostream>
#include "vectors.h"
#include "matrix.h"
#include <cmath>

//default constructor making the unit vector point 
// along z axis
Vector3D::Vector3D()
		:  m_x(0.0), m_y(0.0), m_z(0.0)
{		
	//std::cout <<"Calling default constructor\n";
}
		
//user defined constructor
Vector3D::Vector3D(double x, double y, double z)
		:m_x(x), m_y(y), m_z(z)
{
	//std::cout << "calling user defined constructor\n";
}

//copy constructor
Vector3D::Vector3D(const Vector3D &vector)
		:m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
{
	//std::cout << "calling copy constructor\n";
}

//length square and length functions for vectors		
double lengthSq(const Vector3D &vector)
{
    return ((vector.m_x)*(vector.m_x) + (vector.m_y)*(vector.m_y) + (vector.m_z)*(vector.m_z));
}
        
double length(const Vector3D &vector)
{
    return sqrt(lengthSq(vector));
}

Vector3D normalize(const Vector3D &vector)
{
    std::cout <<"Normalize function invoked\n";
    return (vector/length(vector));
}
	
//destructor 	
Vector3D::~Vector3D()
		{	}

std::ostream& operator<<(std::ostream &out, const Vector3D &vector)
{
	out << "{x,y,z}: {" << vector.m_x << ", " << vector.m_y << ", " << vector.m_z << "}\t";
	return out;
}

//overloaded subscript operator to return vector components
const double& Vector3D::operator[](const int index) const
{
    switch (index)
    {
        case 0 :
            return m_x;
            break;
            
        case 1 : 
            return m_y;
            break;
            
        case 2 : 
            return m_z;
            break;
        
        default : 
            std::cout << "ERROR, unknown vector index\n";
            std::cout << "valid vector index = {0,1,2}\n";
            std::cout << "exiting with return code 1\n";
            exit(1);
    }
}
            

//overloaded assignment operator
Vector3D& Vector3D::operator=(const Vector3D &vector)
{
	std::cout << "Calling overloaded assignment operator on vectors\n";
	this->m_x = vector.m_x;
	this->m_y = vector.m_y;
	this->m_z = vector.m_z;
	
	return *this;
}

//binary operations on vectors
Vector3D operator+(const Vector3D &vector1, const Vector3D &vector2)
{
	return Vector3D((vector1.m_x + vector2.m_x), (vector1.m_y + vector2.m_y), (vector1.m_z + vector2.m_z));
}

Vector3D operator-(const Vector3D &vector1, const Vector3D &vector2)
{
	return Vector3D((vector1.m_x - vector2.m_x), (vector1.m_y - vector2.m_y), (vector1.m_z - vector2.m_z));
}

Vector3D operator*(const Vector3D &vector1, const Vector3D &vector2)
{
   return Vector3D((vector1.m_x*vector2.m_x),(vector1.m_y*vector2.m_y), (vector1.m_z*vector2.m_z));
}

Vector3D operator/(const Vector3D &vector1, const Vector3D &vector2)
{
    return Vector3D((vector1.m_x/vector2.m_x),(vector1.m_y/vector2.m_y), (vector1.m_z/vector2.m_z));
}

/********************** overloaded binary operator ends here***********/



/**** Overloaded unary operator ****************/
Vector3D operator-(const Vector3D &vector)
{
    return Vector3D(-(vector.m_x), -(vector.m_y), -(vector.m_z));
}
/**** Overloaded unary operator ends here ****************/


Vector3D operator*(const double &num, const Vector3D &vector)
{
	return Vector3D(num*vector.m_x, num*vector.m_y, num*vector.m_z);
}

Vector3D operator*(const Vector3D &vector, const double &num)
{
	return num*vector;
}


Vector3D operator/(const Vector3D &vector, const double &num)
{
	if(num==0.0)
	{
	    std::cout << "divide by zero error\n";
	    std::cout << "exiting with return status 1\n";
	    exit(1);
    }
	return vector*(1/num);
}


double dotProduct(const Vector3D &vector1, const Vector3D &vector2)
{
	return ((vector1.m_x*vector2.m_x) + (vector1.m_y*vector2.m_y) + (vector1.m_z*vector2.m_z));
}


//TODO complete corss product
Vector3D crossProduct(const Vector3D &vector1, const Vector3D &vector2)
{
	Vector3D result;
	
	result.m_x = vector1.m_y*vector2.m_z - vector1.m_z*vector2.m_y;
	result.m_y = vector1.m_z*vector2.m_x - vector1.m_x*vector2.m_z;
	result.m_z = vector1.m_x*vector2.m_y - vector1.m_y*vector2.m_x;
	return result;
}

typedef Vector3D Point;

bool Vector3D::isNormalized() const
{
    double TOL{0.00001},magnitude_sq = (m_x*m_x) + (m_y*m_y)+(m_z*m_z);
    
    //int magnitude = static_cast<int>(magnitude_sq);
    
    
    if((magnitude_sq<=1.0+TOL)||(magnitude_sq>=1.0-TOL) )
     {      
       // std::cout << "Magnitude: " << magnitude_sq <<"\n";
       // std::cout << "returning True\n";
        return true;
     }
    
    else
     {   
        //std::cout << "Magnitude: " << magnitude_sq <<"\n";
        //std::cout << "returning false\n";
        return false;      
     }
}
    

/*****************************************************************/
/************************FOR TESTING******************************/
/*****************************************************************	
int main(int argc, char **argv)
{
	std::cout <<"Testing all the functions in Vector3D created so far\n";
	
	Vector3D a;
	
	Vector3D b(4, 3, 0);
	
	std::cout << "length square b " << lengthSq(b) << "\n";
	std::cout << "lenth of b " << length(b) << "\n";
	
	Vector3D c;
	
	c = a + b;
	
	std::cout << "Vector a: "<< a << "\n";
	std::cout << "Vector b: "<< b << "\n";
	std::cout << "Vector c: "<< c << "\n";
	
	Vector3D d(c);
	
	std::cout << "vector d :" << d << "\n";
	std::cout << "normalized d :" << normalize(d) << "\n";
	
	d = 5*d;
	std::cout << "Vector d after pre multiplication: "<< d << "\n";
	
	d = d*2;
	std::cout << "Vector d after post multiplication: "<< d << "\n";
	
	std::cout << d[1] << "\n";
	std::cout << d[0] << "\n";
	std::cout << d[2] << "\n";

	
	return 0;
}
*****************************************************************/
/************************FOR TESTING******************************/
/*****************************************************************/	
