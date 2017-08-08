#ifndef _VECTOR_MATHS_H_
#define _VECTOR_MATHS_H_

template <class T>
inline T square(T number)
{
    return number*number;
}

class Matrix;
//the class Vector3D is for handling various 3D operations needed
//for the ray tracing algorithm
//the axes are aligned according to right hand screw rule and z pointing up
class Vector3D
{
    public:
        double m_x, m_y, m_z;
    
    
        
        //default constructor 
        Vector3D();
        
        //user defined constructor
        Vector3D(double x, double y, double z);
        
        //copy constructor
        Vector3D(const Vector3D &vector);
        
        friend std::ostream& operator<<(std::ostream &out, const Vector3D &vector);
        
        //Square of length and length , unit vector
        friend double lengthSq(const Vector3D &vector);    
        friend double length(const Vector3D &vector);
        friend Vector3D normalize(const Vector3D &vector);
        
        //overloaded  asssignment operators
        Vector3D& operator=(const Vector3D &vector);
        Vector3D& operator+=(const Vector3D &vector);
        Vector3D& operator-=(const Vector3D &vector);
        Vector3D& operator*=(const Vector3D &vector);
        Vector3D& operator/=(const Vector3D &vector);
        
        //to get vector components, index ={0,1,2}
        const double& operator[](const int index) const;

            
        //overloaded binary operators
        friend Vector3D operator+(const Vector3D &vector1, const Vector3D &vector2);
        friend Vector3D operator-(const Vector3D &vector1, const Vector3D &vector2);
        friend Vector3D operator*(const Vector3D &vector1, const Vector3D &vector2);  //use carefully
        friend Vector3D operator/(const Vector3D &vector1, const Vector3D &vector2);  //use carefully
        
        //overloaded unary operators
        friend Vector3D operator-(const Vector3D &vector);

       
        //scaling functions for vectors
        friend Vector3D operator*(const double &num, const Vector3D &vector);
        friend Vector3D operator*(const Vector3D &vector, const double &num);
        friend Vector3D operator/(const Vector3D &vector, const double &num);
        
        //scalar and vector products
        friend double dotProduct(const Vector3D &vector1, const Vector3D &vector2);
        friend Vector3D crossProduct(const Vector3D &vector1, const Vector3D &vector3D);  
        
        virtual ~Vector3D();
};

#endif

