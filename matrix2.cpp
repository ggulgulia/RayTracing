#include <cmath>
#include <iostream>
#include <iomanip>
#include "matrix.h"
#include "vectors.h"

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

//this function takes a location as input and constructs a 
//translation matrix 
Matrix translationMatrix(const Vector3D &location)
{
    Matrix M = eye();
    M.m_matrix[3][0] = location.m_x;
    M.m_matrix[3][1] = location.m_y;
    M.m_matrix[3][2] = location.m_z;
    
    return M;
}

//constructs a matrix rotated about x axis by given angle
//angle is specified in degrees
Matrix rotationXMatrix(const double angle)
{
 Matrix M = eye();
 double radians = pi*angle/180.00; 
 double Cosine = cos(radians);
 double Sine = sin(angle);
 
 M.m_matrix[1][1] = Cosine;
 M.m_matrix[2][1] = -Sine;
 M.m_matrix[1][2] = Sine;
 M.m_matrix[2][2] = Cosine;
 
 return M;
}


//constructs a matrix rotated about x axis by given angle
//angle is specified in degrees
Matrix rotationYMatrix(const double angle)
{
 Matrix M = eye();
 double radians = pi*angle/180.00; 
 double Cosine = cos(radians);
 double Sine = sin(angle);
 
 M.m_matrix[0][0] = Cosine;
 M.m_matrix[2][0] = -Sine;
 M.m_matrix[0][2] = Sine;
 M.m_matrix[2][2] = Cosine;
 
 return M;
}


//constructs a matrix rotated about x axis by given angle
//angle is specified in degrees
Matrix rotationZMatrix(const double angle)
{
 Matrix M = eye();
 double radians = pi*angle/180.00; 
 double Cosine = cos(radians);
 double Sine = sin(angle);
 
 M.m_matrix[0][0] = Cosine;
 M.m_matrix[1][0] = -Sine;
 M.m_matrix[0][1] = Sine;
 M.m_matrix[1][1] = Cosine;
 
 return M;
}

//constructs a yaw pitch roll rotation matrix
//angles about x-y axis, rotates pitch angles in plane defined by the yaw rotation
//and rotate roll angles aboutthe previous two angles
Matrix rotationYPRMatrix(const double yaw, const double pitch, const double roll)
{
    double yawR = yaw*pi/180.0;
    double pitchR = pitch*pi/180;
    double rollR = roll*pi/180;
    
    Matrix M;    
    double cy = cos(yawR);
    double sy = sin(yawR);
    double cp = cos(pitchR);
    double sp = sin(pitchR);
    double cr = cos(rollR);
    double sr = sin(rollR);
    
    M.m_matrix[0][0] = cy*cr + sy*sp*sr;
    M.m_matrix[1][0] = -cy*sr +sy*sp*cr;
    M.m_matrix[2][0] = sy*cp;
    M.m_matrix[0][1] = sr*cp;
    M.m_matrix[1][1] = cr*cp;
    M.m_matrix[2][1] = -sp;
    M.m_matrix[0][2] = -sy*cr - cy*sp*sr;
    M.m_matrix[1][2] = sr*sy + cy*sp*cr;
    M.m_matrix[2][2] = cy*cp;
    
    
    M.m_matrix[3][3] = 1.0; 
    
    return M;
}


//construct a rotation of a given angle about a given axis
//derived from Eric Haines's SPD
Matrix rotationAxisMatrix(const Vector3D &axis, double angle)
{
  Matrix M;
  double radians = pi*angle/180.0;
  
  double cosine = cos(radians);
  double sine = sin(radians);
  
  double one_minus_cosine = 1.0 - cosine;
  
  M.m_matrix[0][0] = axis.m_x*axis.m_y + (1.0 - (axis.m_x*axis.m_x))*cosine;
  M.m_matrix[0][1] = axis.m_x*axis.m_y + one_minus_cosine + axis.m_z*sine;
  M.m_matrix[0][2] = axis.m_x*axis.m_y + one_minus_cosine - axis.m_y*sine;
  
  M.m_matrix[1][0] = axis.m_x*axis.m_y + one_minus_cosine - axis.m_z*sine;
  M.m_matrix[1][1] = axis.m_x*axis.m_y + (1.0 - (axis.m_y*axis.m_y))*cosine;
  M.m_matrix[1][2] = axis.m_y*axis.m_z + one_minus_cosine + axis.m_x*sine;
  
  M.m_matrix[2][0] = axis.m_x*axis.m_z + one_minus_cosine + axis.m_y*sine;
  M.m_matrix[2][1] = axis.m_y*axis.m_z + one_minus_cosine - axis.m_x*sine;
  M.m_matrix[2][2] = axis.m_z*axis.m_z + (1.0 - (axis.m_z*axis.m_z))*cosine;
  
  M.m_matrix[3][3] = 1.0;
  
  return M; 
}

//constructs a scaled matrix, given x, y, and z parameters
//to scale uniformly x=y=z
Matrix ScaleMatrix(double x, double y, double z)
{
    Matrix M = eye();
    
    M.m_matrix[0][0] = x;
    M.m_matrix[1][1] = y;
    M.m_matrix[2][2] = z;
    
    return M;
}

//constructs a rotation matrix that makes the x, y and z a
//axis corresponding to the given vector
Matrix genRotation(const Vector3D &x, const Vector3D &y, const Vector3D &z)
{
    Matrix M = eye();
    
    M.m_matrix[0][0] = x.m_x;
    M.m_matrix[1][0] = x.m_y;
    M.m_matrix[2][0] = x.m_x;
    
    M.m_matrix[0][1] = y.m_x;
    M.m_matrix[1][1] = y.m_y;
    M.m_matrix[2][1] = y.m_z;
    
    M.m_matrix[0][2] = z.m_x;
    M.m_matrix[1][2] = z.m_y;
    M.m_matrix[2][2] = z.m_z;
    
    return M;
}

//construct a view matrix to rotate and translate the world
//the viewer is located at 'viewer' and looking at 'lookAt' and 
//the up vector is at uppp'up'. The transformation changes 
//things around so the viewer is at origin and looking down at -z axis

/*************************************************************************************
Matrix viewMatrix(const Vector3D &lookAt, const Vector3D &viewer, const Vector3D &up)
{

}


Matrix quadricMatrix(double a, double b, double c, double d, double e, double f,
                          double g, double h, double i, double j, double k)
{
   
}


Matrix MirrorX()
{

}


Matrix MirrorY()
{

}


Matrix MirrorZ()
{

}


Matrix RotationOnly(const Matrix &x)
{

}
*************************************************************************************/
