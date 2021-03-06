
#include "Vector3.h"
#include <Engine/Math/Angle/Angle.h>
#include <Engine/Math/Rotation/AxisAngle/AxisAngle.h>
#include <Engine/Math/Vector/Vector2/Vector2.h>



const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);
const int32 Vector3::SIZE = 3;


Vector3::Vector3(void): x(0.0f), y(0.0f), z(0.0f)
{}


Vector3::Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z)
{}


Vector3::Vector3(Spherical _spherical)
{
	FromSpherical(_spherical);
}



void Vector3::Set(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}


void Vector3::Normalize(void)
{ 
	float length = GetLength();

	if(length != 0.0f)
	{
		length = 1.0f / length;
		(*this) *= length;
	}
}


Vector3 Vector3::_GetNormalize(Vector3 _vector)
{ 
	Vector3 vector = _vector;
	vector.Normalize();
	return vector;
}



Vector3 Vector3::operator * (float _scalar)const 
{
	return Vector3(x * _scalar, y * _scalar, z * _scalar); 
}
	

Vector3& Vector3::operator *= (float _scalar)
{ 
	x *= _scalar; 
	y *= _scalar; 
	z *= _scalar;
	return *this;   
}



Vector3 Vector3::operator / (float _scalar)const 
{ 
	if(_scalar != 0.0f)
	{
		return Vector3(x / _scalar, y / _scalar, z / _scalar); 
	}
	return Vector3();
}
	

Vector3& Vector3::operator /= (float _scalar)
{ 
	if(_scalar != 0.0f)
	{
		x /= _scalar; 
		y /= _scalar; 
		z /= _scalar;
		return *this;   
	}
	x = y = z = 0.0f;
	return *this;   
}


Vector3 Vector3::operator + (const Vector3& _vector)const 
{ 
	return Vector3(x + _vector.x, y + _vector.y, z + _vector.z); 
}



Vector3& Vector3::operator += (Vector3 _vector)
{
	x += _vector.x; 
	y += _vector.y; 
	z += _vector.z;
	return *this;	
}



Vector3 Vector3::operator - (const Vector3& _vector)const 
{ 
	return Vector3(x -_vector.x, y - _vector.y, z - _vector.z); 
}


Vector3& Vector3::operator -= (Vector3 _vector)
{ 
	x -= _vector.x; 
	y -= _vector.y; 
	z -= _vector.z;
	return *this;	
}



bool Vector3::operator == (const Vector3& _vector)const 
{ 
	return (x == _vector.x && y == _vector.y && z == _vector.z);	
}


bool Vector3::operator != (const Vector3& _vector)const 
{ 
	return !(*this == _vector);
}


float Vector3::GetNorm(void)const 
{
	return x * x + y * y + z * z;
}


float Vector3::GetLength(void)const 
{
	return sqrtf(x * x + y * y + z * z);
}


float Vector3::_GetLength(Vector3 _vector)
{
	return _vector.GetLength();
}



float Vector3::GetDot(const Vector3& _vector)const 
{ 
	return x * _vector.x + y * _vector.y + z * _vector.z;
}
	

float Vector3::_GetDot(Vector3 _vector1, Vector3 _vector2)
{ 
	return _vector1.GetDot(_vector2);
}




Vector3 Vector3::_GetInverse(Vector3 _vector)
{
	return -_vector;
}



Vector3 Vector3::Project(Vector3 _vector)
{
	return _vector * (Vector3::_GetDot(_vector, (*this)) / (Vector3::_GetDot(_vector, _vector)));
}


Vector3 Vector3::Reject(Vector3 _vector)
{
	return (*this) - Project(_vector);

}


Vector3 Vector3::operator - (void)const 
{ 
	return Vector3(-x, -y, -z);
}


void Vector3::Inverse(void)
{
	x = -x;
	y = -y;
	z = -z;
}


float Vector3::operator / (const Vector3& _vector)const
{
	return x * _vector.x + y * _vector.y + z * _vector.z;
}



Vector3 Vector3::operator * (const Vector3& _vector)const
{
	Vector3 vector;

	vector.x = (y * _vector.z) - (z * _vector.y);
	vector.y = (z * _vector.x) - (x * _vector.z);
	vector.z = (x * _vector.y) - (y * _vector.x); 

	return vector;
}



Vector3& Vector3::operator *= (Vector3 _vector)
{
	(*this) = Vector3((y * _vector.z) - (z * _vector.y),
		              (z * _vector.x) - (x * _vector.z),
					  (x * _vector.y) - (y * _vector.x));
	return *this;
}


Vector3 Vector3::_GetCross(Vector3 _vector1, Vector3 _vector2)
{ 
	return _vector1 * _vector2;
}




void Vector3::RotateX(float _angle)
{
	Vector3 vector;

	float cosAngle = cosf(_angle);
	float sinAngle = sinf(_angle);

	vector.y = y * cosAngle - z * sinAngle;
    vector.z = y * sinAngle + z * cosAngle;
	vector.x = x;

	x = vector.x;
	y = vector.y;
	z = vector.z;
}


void Vector3::RotateY(float _angle)
{
	Vector3 vector;

	float cosAngle = cosf(_angle);
	float sinAngle = sinf(_angle);

	vector.z = z * cosAngle - x * sinAngle;
    vector.x = z * sinAngle + x * cosAngle;
	vector.y = y;

	x = vector.x;
	y = vector.y;
	z = vector.z;
}


void Vector3::RotateZ(float _angle)
{
	Vector3 vector;

	float cosAngle = cosf(_angle);
	float sinAngle = sinf(_angle);

	vector.x = x * cosAngle - y * sinAngle;
	vector.y = x * sinAngle + y * cosAngle;
	vector.z = z;

	x = vector.x;
	y = vector.y;
	z = vector.z;
}
 


void Vector3::RotateAxisAngle(AxisAngle _axisAngle)
{
	Vector3 vector;

	float cosAngle = cosf(_axisAngle.angle);
	float sinAngle = sinf(_axisAngle.angle);

	vector.x = _GetDot((*this), Vector3((1.0f - cosAngle) * (_axisAngle.axis.x * _axisAngle.axis.x) + cosAngle, 
	                                    (1.0f - cosAngle) * (_axisAngle.axis.y * _axisAngle.axis.x) - (sinAngle * _axisAngle.axis.z), 
	                                    (1.0f - cosAngle) * (_axisAngle.axis.z * _axisAngle.axis.x) + (sinAngle * _axisAngle.axis.y)));

	vector.y = _GetDot((*this), Vector3((1.0f - cosAngle) * (_axisAngle.axis.x * _axisAngle.axis.y) + (sinAngle * _axisAngle.axis.z),
	                                    (1.0f - cosAngle) * (_axisAngle.axis.y * _axisAngle.axis.y) + cosAngle,
	                                    (1.0f - cosAngle) * (_axisAngle.axis.z * _axisAngle.axis.y) - (sinAngle * _axisAngle.axis.x)));

	vector.z = _GetDot((*this), Vector3((1.0f - cosAngle) * (_axisAngle.axis.x * _axisAngle.axis.z) - (sinAngle * _axisAngle.axis.y),
                                        (1.0f - cosAngle) * (_axisAngle.axis.y * _axisAngle.axis.z) + (sinAngle * _axisAngle.axis.x),
	                                    (1.0f - cosAngle) * (_axisAngle.axis.z * _axisAngle.axis.z) + cosAngle));
	x = vector.x;
	y = vector.y;
	z = vector.z;
} 




void Vector3::FromSpherical(Spherical _spherical)
{
	x = _spherical.radius * cosf(_spherical.vertical) * sinf(_spherical.horizontal);
	y = _spherical.radius * sinf(_spherical.vertical);
	z = _spherical.radius * cosf(_spherical.vertical) * cosf(_spherical.horizontal);
}

Vector3 Vector3::_FromSpherical(Spherical _spherical)
{
	Vector3 vector;
	vector.FromSpherical(_spherical);
	return vector;
}


Spherical Vector3::ToSpherical(void)const
{
	float r = GetLength();
	
	float v = atan2f(y, sqrtf(z * z + x * x));
	float h =  atan2f(x, z);

	return Spherical(r, v, h);
}


Spherical Vector3::_ToSpherical(Vector3 _vector)
{
	return _vector.ToSpherical();
}



float& Vector3::operator [] (int32 _index)
{ 
	return *(&x + _index);
}
	
float Vector3::operator [] (int32 _index)const
{ 
	return *(&x + _index);
}



Vector3 Vector3::_RotateX(Vector3 _vector, float _angle)
{  
	Vector3 vector = _vector;
	vector.RotateX(_angle);
	return vector;
}


Vector3 Vector3::_RotateY(Vector3 _vector, float _angle)
{
	Vector3 vector = _vector;
	vector.RotateY(_angle);
	return vector;
}


Vector3 Vector3::_RotateZ(Vector3 _vector, float _angle)
{
	Vector3 vector = _vector;
	vector.RotateZ(_angle);
	return vector;
} 



Vector3 Vector3::_FromTo(Vector3 _from, Vector3 _to)
{
	return _to - _from;
}



float Vector3::_GetAngle(Vector3 _vector1, Vector3 _vector2)
{
	return acosf(Vector3::_GetDot(Vector3::_GetNormalize(_vector1), Vector3::_GetNormalize(_vector2)));
}



float Vector3::GetAngleZ(void)const
{ 
	return atan2f(y, x);
} 

float Vector3::GetAngleX(void)const
{ 
	return atan2f(z, y);
}

float Vector3::GetAngleY(void)const
{ 
	return atan2f(x, z);
} 


float Vector3::_GetAngleX(Vector3 _vector)
{
	return _vector.GetAngleX();
}


float Vector3::_GetAngleY(Vector3 _vector)
{
	return _vector.GetAngleY();
}


float Vector3::_GetAngleZ(Vector3 _vector)
{
	return _vector.GetAngleZ();
}



Vector2 Vector3::ToVector2(void)
{
	return Vector2(x, y);
}



Vector2 Vector3::_ToVector2(Vector3 _vector)
{
	return Vector2(_vector.x, _vector.y);
}

		

Vector3 Vector3::_FromVector2(Vector2 _vector)
{
	return Vector3(_vector.x, _vector.y, 0.0f);
}