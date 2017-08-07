#include <cmath>
#include <iostream>
#include <iomanip>
#include "matrix.h"
#include "vectors.h"


//default constructor initializing all elements to zero
Matrix::Matrix()
{
	std::cout << "Calling default constructor for matrix\n";
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			m_matrix[i][j] = 0.0;
		}
	}
}

//copy constructor doing a deep copy
Matrix::Matrix(const Matrix &A)
{
	std::cout << "Calling copy constructor on the matrix\n";
	
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			m_matrix[i][j] = A.m_matrix[i][j];
		}
	}
}

//overloaded output operator
std::ostream& operator<<(std::ostream &out , const Matrix &A)
{
	out << "printing the matrix \n";
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			out << std::setprecision(4) << std::setw(10) << A.m_matrix[i][j];
		}
		out << "\n";
	}
	out << "\n";
	return out;
}
	

//destructor
Matrix::~Matrix() {	}


//overloaded assignment operators
Matrix& Matrix::operator=(const Matrix &A)
{
	std::cout << "Calling the overloaded assignment operator\n";
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			this->m_matrix[i][j] = A.m_matrix[i][j];
		}
	}
	return *this;

}

Matrix& Matrix::operator+=(const Matrix &A)
{
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			this->m_matrix[i][j] += A.m_matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix &A)
{
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			this->m_matrix[i][j] -= A.m_matrix[i][j];
		}
	}
	
	return *this;
}

//overloaded binary operators
Matrix Matrix::operator+(const Matrix &A)
{
	Matrix newMatrix;
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			newMatrix.m_matrix[i][j] = this->m_matrix[i][j] + A.m_matrix[i][j];
		}
	}
	
	return newMatrix;
}
	
Matrix Matrix::operator-(const Matrix &A)
{
	Matrix newMatrix;
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			newMatrix.m_matrix[i][j] = this->m_matrix[i][j] - A.m_matrix[i][j];
		}
	}
	
	return newMatrix;
}

Matrix scale(const Matrix &A, const double &num)
{
	Matrix M;
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			M.m_matrix[i][j] = A.m_matrix[i][j]*num;
		}
	}
	
	return M;
}


//useful matrices
Matrix ones()
{
	Matrix oneMat;
	for(int i=0; i<D; ++i)
	{
		for(int j=0; j<D; ++j)
		{
			oneMat.m_matrix[i][j] = 1.0;
		}
	}
	
	return oneMat;
}

Matrix eye()
{
	Matrix I;
	I.m_matrix[0][0] = 1.00;
	I.m_matrix[1][1] = 1.00;
	I.m_matrix[2][2] = 1.00;
	I.m_matrix[3][3] = 1.00;
	
	return I;
}

Matrix zeros()
{
	return Matrix();
}

//fundamental matrix operations

//determinants
double det(const Matrix &A )
{
	double val = 0.0; //garbage value
	
	val = (A.m_matrix[0][0] * A.m_matrix[1][1] * A.m_matrix[2][2] * A.m_matrix[3][3]) 
		+ (A.m_matrix[0][0] * A.m_matrix[1][2] * A.m_matrix[2][3] * A.m_matrix[3][1])
		+ (A.m_matrix[0][0] * A.m_matrix[1][3] * A.m_matrix[2][1] * A.m_matrix[3][2]) 
		
		+ (A.m_matrix[0][1] * A.m_matrix[1][0] * A.m_matrix[2][3] * A.m_matrix[3][2])
		+ (A.m_matrix[0][1] * A.m_matrix[1][2] * A.m_matrix[2][0] * A.m_matrix[3][3])
		+ (A.m_matrix[0][1] * A.m_matrix[1][3] * A.m_matrix[2][2] * A.m_matrix[3][0])
		
		+ (A.m_matrix[0][2] * A.m_matrix[1][0] * A.m_matrix[2][1] * A.m_matrix[3][3])
		+ (A.m_matrix[0][2] * A.m_matrix[1][1] * A.m_matrix[2][3] * A.m_matrix[3][0])
		+ (A.m_matrix[0][2] * A.m_matrix[1][3] * A.m_matrix[2][0] * A.m_matrix[3][1])
		
		+ (A.m_matrix[0][3] * A.m_matrix[1][0] * A.m_matrix[2][2] * A.m_matrix[3][1])
		+ (A.m_matrix[0][3] * A.m_matrix[1][1] * A.m_matrix[2][0] * A.m_matrix[3][2])
		+ (A.m_matrix[0][3] * A.m_matrix[1][2] * A.m_matrix[2][1] * A.m_matrix[3][0])
		
		- (A.m_matrix[0][0] * A.m_matrix[1][1] * A.m_matrix[2][3] * A.m_matrix[3][2])
		- (A.m_matrix[0][0] * A.m_matrix[1][2] * A.m_matrix[2][1] * A.m_matrix[3][3])
		- (A.m_matrix[0][0] * A.m_matrix[1][3] * A.m_matrix[2][2] * A.m_matrix[3][1])
		
		- (A.m_matrix[0][1] * A.m_matrix[1][0] * A.m_matrix[2][2] * A.m_matrix[3][3])
		- (A.m_matrix[0][1] * A.m_matrix[1][2] * A.m_matrix[2][3] * A.m_matrix[3][0])
		- (A.m_matrix[0][1] * A.m_matrix[1][3] * A.m_matrix[2][0] * A.m_matrix[3][2])
		
		- (A.m_matrix[0][2] * A.m_matrix[1][0] * A.m_matrix[2][3] * A.m_matrix[3][1])
		- (A.m_matrix[0][2] * A.m_matrix[1][1] * A.m_matrix[2][0] * A.m_matrix[3][3])
		- (A.m_matrix[0][2] * A.m_matrix[1][3] * A.m_matrix[2][1] * A.m_matrix[3][0])
		
		- (A.m_matrix[0][3] * A.m_matrix[1][0] * A.m_matrix[2][1] * A.m_matrix[3][2])
		- (A.m_matrix[0][3] * A.m_matrix[1][1] * A.m_matrix[2][2] * A.m_matrix[3][0])
		- (A.m_matrix[0][3] * A.m_matrix[1][2] * A.m_matrix[2][0] * A.m_matrix[3][1]);
				
	return val;
	
}

Matrix inv(const Matrix &A)
{
    if(det(A) == 0)
    {
        std::cout << "dterminant of the matrix is zero\n";
        std::cout << "given matrix cannot be inverted\n";
        exit(1);
    }
    
    
    Matrix B;
    B.m_matrix[0][0] = A.m_matrix[1][1] * A.m_matrix[2][2] * A.m_matrix[3][3] 
                     + A.m_matrix[1][2] * A.m_matrix[2][3] * A.m_matrix[3][1]
                     + A.m_matrix[1][3] * A.m_matrix[2][1] * A.m_matrix[3][2] 
                     
                     - A.m_matrix[1][1] * A.m_matrix[2][3] * A.m_matrix[3][2]
	                 - A.m_matrix[1][2] * A.m_matrix[2][1] * A.m_matrix[3][3]
	                 - A.m_matrix[1][3] * A.m_matrix[2][2] * A.m_matrix[3][1];
	                 
    
    B.m_matrix[0][1] = A.m_matrix[0][1] * A.m_matrix[2][3] * A.m_matrix[3][2]
                     + A.m_matrix[0][2] * A.m_matrix[2][1] * A.m_matrix[3][3]
                     + A.m_matrix[0][3] * A.m_matrix[2][2] * A.m_matrix[3][1]
                     
                     - A.m_matrix[0][1] * A.m_matrix[2][2] * A.m_matrix[3][3]
                     - A.m_matrix[0][3] * A.m_matrix[2][1] * A.m_matrix[3][2]
                     - A.m_matrix[0][3] * A.m_matrix[2][1] * A.m_matrix[3][2];
                     
    
    B.m_matrix[0][2] = A.m_matrix[0][1] * A.m_matrix[1][2] * A.m_matrix[3][3]
                     + A.m_matrix[0][2] * A.m_matrix[1][3] * A.m_matrix[3][1]
                     + A.m_matrix[0][3] * A.m_matrix[1][1] * A.m_matrix[3][2]
                     
                     - A.m_matrix[0][1] * A.m_matrix[1][3] * A.m_matrix[3][2]
                     - A.m_matrix[0][2] * A.m_matrix[1][1] * A.m_matrix[3][3]
                     - A.m_matrix[0][3] * A.m_matrix[1][2] * A.m_matrix[3][1];
   
    
    B.m_matrix[0][3] = A.m_matrix[0][1] * A.m_matrix[1][3] * A.m_matrix[2][2]
                     + A.m_matrix[0][2] * A.m_matrix[1][1] * A.m_matrix[2][3]
                     + A.m_matrix[0][3] * A.m_matrix[1][2] * A.m_matrix[2][1]
                     
                     - A.m_matrix[0][1] * A.m_matrix[1][2] * A.m_matrix[2][3]
                     - A.m_matrix[0][2] * A.m_matrix[1][3] * A.m_matrix[2][1]
                     - A.m_matrix[0][3] * A.m_matrix[1][1] * A.m_matrix[2][2];
      
                     
    B.m_matrix[1][0] = A.m_matrix[1][0] * A.m_matrix[2][3] * A.m_matrix[3][2]
                     + A.m_matrix[1][2] * A.m_matrix[2][0] * A.m_matrix[3][3]
                     + A.m_matrix[1][3] * A.m_matrix[2][2] * A.m_matrix[3][0]
                     
                     - A.m_matrix[1][0] * A.m_matrix[2][2] * A.m_matrix[3][3]
                     - A.m_matrix[1][2] * A.m_matrix[2][3] * A.m_matrix[3][0]
                     - A.m_matrix[1][3] * A.m_matrix[2][0] * A.m_matrix[3][2];
    
    
    B.m_matrix[1][1] = A.m_matrix[0][0] * A.m_matrix[2][2] * A.m_matrix[3][3]
                     + A.m_matrix[0][2] * A.m_matrix[2][3] * A.m_matrix[3][0]
                     + A.m_matrix[0][3] * A.m_matrix[2][0] * A.m_matrix[3][2]
                     
                     - A.m_matrix[0][0] * A.m_matrix[2][3] * A.m_matrix[3][2]
                     - A.m_matrix[0][2] * A.m_matrix[2][0] * A.m_matrix[3][3]
                     - A.m_matrix[0][3] * A.m_matrix[2][2] * A.m_matrix[3][0];
    
    
    B.m_matrix[1][2] = A.m_matrix[0][0] * A.m_matrix[1][3] * A.m_matrix[3][2]
                     + A.m_matrix[0][2] * A.m_matrix[1][0] * A.m_matrix[3][3]
                     + A.m_matrix[0][3] * A.m_matrix[1][2] * A.m_matrix[3][0]
                     
                     - A.m_matrix[0][0] * A.m_matrix[1][2] * A.m_matrix[3][3]
                     - A.m_matrix[0][2] * A.m_matrix[1][3] * A.m_matrix[3][0]
                     - A.m_matrix[0][3] * A.m_matrix[1][0] * A.m_matrix[3][2];
    
    
    B.m_matrix[1][3] = A.m_matrix[0][0] * A.m_matrix[1][2] * A.m_matrix[2][3]
                     + A.m_matrix[0][2] * A.m_matrix[1][3] * A.m_matrix[2][0]
                     + A.m_matrix[0][3] * A.m_matrix[1][0] * A.m_matrix[2][2]
                     
                     - A.m_matrix[0][0] * A.m_matrix[1][3] * A.m_matrix[2][2]
                     - A.m_matrix[0][2] * A.m_matrix[1][0] * A.m_matrix[2][3]
                     - A.m_matrix[0][3] * A.m_matrix[1][2] * A.m_matrix[2][0];
    
    
    B.m_matrix[2][0] = A.m_matrix[1][0] * A.m_matrix[2][1] * A.m_matrix[3][3]
                     + A.m_matrix[1][1] * A.m_matrix[2][3] * A.m_matrix[3][0]
                     + A.m_matrix[1][3] * A.m_matrix[2][0] * A.m_matrix[3][1]
                     
                     - A.m_matrix[1][0] * A.m_matrix[2][3] * A.m_matrix[3][1]
                     - A.m_matrix[1][1] * A.m_matrix[2][0] * A.m_matrix[3][3]
                     - A.m_matrix[1][3] * A.m_matrix[2][1] * A.m_matrix[3][0];
    
    
    B.m_matrix[2][1] = A.m_matrix[0][0] * A.m_matrix[2][3] * A.m_matrix[3][1]
                     + A.m_matrix[0][1] * A.m_matrix[2][0] * A.m_matrix[3][3]
                     + A.m_matrix[0][3] * A.m_matrix[2][1] * A.m_matrix[3][0]
                     
                     - A.m_matrix[0][0] * A.m_matrix[2][1] * A.m_matrix[3][3]
                     - A.m_matrix[0][1] * A.m_matrix[2][3] * A.m_matrix[3][0]
                     - A.m_matrix[0][3] * A.m_matrix[2][0] * A.m_matrix[3][1];
    
    
    B.m_matrix[2][2] = A.m_matrix[0][0] * A.m_matrix[1][1] * A.m_matrix[3][3]
                     + A.m_matrix[0][1] * A.m_matrix[1][3] * A.m_matrix[3][0]
                     + A.m_matrix[0][3] * A.m_matrix[1][0] * A.m_matrix[3][1]
                     
                     - A.m_matrix[0][0] * A.m_matrix[1][3] * A.m_matrix[3][1]
                     - A.m_matrix[0][1] * A.m_matrix[1][0] * A.m_matrix[3][3]
                     - A.m_matrix[0][3] * A.m_matrix[1][1] * A.m_matrix[3][1];
    
    
    B.m_matrix[2][3] = A.m_matrix[0][0] * A.m_matrix[1][3] * A.m_matrix[2][1]
                     + A.m_matrix[0][1] * A.m_matrix[1][0] * A.m_matrix[2][3]
                     + A.m_matrix[0][3] * A.m_matrix[1][1] * A.m_matrix[2][0]
                     
                     - A.m_matrix[0][0] * A.m_matrix[1][1] * A.m_matrix[2][3]
                     - A.m_matrix[0][1] * A.m_matrix[1][3] * A.m_matrix[2][0]
                     - A.m_matrix[0][3] * A.m_matrix[1][0] * A.m_matrix[2][1];
    
    
    B.m_matrix[3][0] = A.m_matrix[1][0] * A.m_matrix[2][2] * A.m_matrix[3][1]
                     + A.m_matrix[1][1] * A.m_matrix[2][0] * A.m_matrix[3][2]
                     + A.m_matrix[1][2] * A.m_matrix[2][1] * A.m_matrix[3][0]
                     
                     - A.m_matrix[1][0] * A.m_matrix[2][1] * A.m_matrix[3][2]
                     - A.m_matrix[1][1] * A.m_matrix[2][2] * A.m_matrix[3][0]
                     - A.m_matrix[1][2] * A.m_matrix[2][0] * A.m_matrix[3][1];
    
    
    B.m_matrix[3][1] = A.m_matrix[0][0] * A.m_matrix[2][1] * A.m_matrix[3][2]
                     + A.m_matrix[0][1] * A.m_matrix[2][2] * A.m_matrix[3][0]
                     + A.m_matrix[0][2] * A.m_matrix[2][0] * A.m_matrix[3][1]
                     
                     - A.m_matrix[0][0] * A.m_matrix[2][2] * A.m_matrix[3][1]
                     - A.m_matrix[0][1] * A.m_matrix[2][0] * A.m_matrix[3][2]
                     - A.m_matrix[0][2] * A.m_matrix[2][1] * A.m_matrix[3][0];
    
    
    B.m_matrix[3][2] = A.m_matrix[0][0] * A.m_matrix[1][2] * A.m_matrix[3][1]
                     + A.m_matrix[0][1] * A.m_matrix[1][0] * A.m_matrix[3][2]
                     + A.m_matrix[0][2] * A.m_matrix[1][1] * A.m_matrix[3][0]
                     
                     - A.m_matrix[0][0] * A.m_matrix[1][1] * A.m_matrix[3][2]
                     - A.m_matrix[0][1] * A.m_matrix[1][2] * A.m_matrix[3][0]
                     - A.m_matrix[0][2] * A.m_matrix[1][0] * A.m_matrix[3][1];
    
    
    B.m_matrix[3][3] = A.m_matrix[0][0] * A.m_matrix[1][1] * A.m_matrix[2][2]
                     + A.m_matrix[0][1] * A.m_matrix[1][2] * A.m_matrix[2][0]
                     + A.m_matrix[0][2] * A.m_matrix[1][0] * A.m_matrix[2][1]
                     
                     - A.m_matrix[0][0] * A.m_matrix[1][2] * A.m_matrix[2][1]
                     - A.m_matrix[0][1] * A.m_matrix[1][0] * A.m_matrix[2][2]
                     - A.m_matrix[0][2] * A.m_matrix[1][1] * A.m_matrix[2][0];
    
    return scale(B, 1/det(A));

}   
    
	

/*****************************************************************/
/************************FOR TESTING******************************/
/*****************************************************************/	
int main(int argc, char **argv)
{
	std::cout << std::setprecision(4);
	std::cout << "testing all matrix class functions created so far\n";
	
	Matrix A;
	std::cout << A;
	
	//Matrix B(A);
	
	Matrix oneMatrix = ones();
	std::cout << oneMatrix;
	
	Matrix I = eye();
	std::cout << I;
	
	A = scale(oneMatrix, 1) + I;
	std::cout << A;
	std::cout << "determinant of A = " << det(A) <<"\n";
	std::cout << "inverse of A = " << inv(A) << "\n";
	
	Matrix C = zeros();
	
	return 0;
}

/*****************************************************************/
/************************FOR TESTING******************************/
/*****************************************************************/	  
