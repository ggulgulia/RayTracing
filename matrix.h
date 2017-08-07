#ifndef _MATRIX_
#define _MATRIX_

#define D 4
#define pi 3.1415926535897932384626433832795

//forward declaration of class
class Vector3D;

class Matrix
{
    private:
        double m_matrix[D][D];
    
    public:
    
      //default constructor
      //initalizes matrix with zero elements
      Matrix();
      
      //copy constructor
      Matrix(const Matrix &A);
      
      //destructor
      virtual ~Matrix();

      
      //overloaded output operator
      friend std::ostream& operator<<(std::ostream &out, const Matrix &A);
      
      //assignment operators
      Matrix& operator=(const Matrix &A);
      Matrix& operator+=(const Matrix &A);
      Matrix& operator-=(const Matrix &A);
      
      //overloaded binary operators , this returns a new matrix rather 
      //than changing the implicit *this matrix
      Matrix operator+(const Matrix &A);
      Matrix operator-(const Matrix &A);
      
      //scaling operation on matrix 
      friend Matrix scale(const Matrix &A, const double &num);
      
      
      
      //useful matrices
      friend Matrix eye();
      friend Matrix ones();
      friend Matrix zeros();
      friend Matrix translationMatrix(const Vector3D &location);
      friend Matrix rotationXMatrix(const double angle);
      friend Matrix rotationYMatrix(const double angle);
      friend Matrix rotationZMatrix(const double angle);
      friend Matrix rotationYPRMatrix(const double yaw, const double pitch, const double roll);
      friend Matrix rotationAxisMatrix(const Vector3D &axis, double angle);
      friend Matrix ScaleMatrix(double x, double y, double z);
      friend Matrix genRotation(const Vector3D &x, const Vector3D &y, const Vector3D &z);
      friend Matrix viewMatrix(const Vector3D &lookAt, const Vector3D &viewer, const Vector3D &up);
      friend Matrix quadricMatrix(double a, double b, double c, double d, double e, double f,
                                  double g, double h, double i, double j, double k);
      friend Matrix MirrorX();
      friend Matrix MirrorY();
      friend Matrix MirrorZ();
      friend Matrix RotationOnly(const Matrix &x);
      
      //fundamental operations on matrix
      friend double det(const Matrix &A);
      friend Matrix inv(const Matrix &A);
      friend Matrix trans(const Matrix &A);   
};
      
#endif
      
