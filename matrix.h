#ifndef _MATRIX_
#define _MATRIX_

#define D 4

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
      
      //fundamental operations on matrix
      friend double det(const Matrix &A);
      friend Matrix inv(const Matrix &A);
      friend Matrix trans(const Matrix &A);   
};
      
#endif
      
