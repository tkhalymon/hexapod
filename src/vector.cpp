#include <math.h>
#include "vector.hpp"

const double Vector::PI = acos(-1);

Vector::Vector() : latency(0), longitude(0), rotation(0)
{

}

Vector::Vector(double lat, double lon, double rot) : latency(lat), longitude(lon), rotation(rot)
{

}

Vector::Vector(const Vector& v) : latency(v.latency), longitude(v.longitude), rotation(v.rotation)
{

}

Vector::Vector(const Vertex& v)
{
	if (v.l() == 0)
	{
		latency = 0;
		longitude = 0;
	}
	else
	{
		latency = v.y() < 0 ? acos(v.x() / v.l()) : 2 * PI - acos(v.x() / v.l());
		longitude = acos(v.y() / v.l());
	}
	rotation = 0;
}

Vector::~Vector()
{
	
}

double& Vector::lat()
{
	return latency;
}

double& Vector::lon()
{
	return longitude;
}

double& Vector::rot()
{
	return rotation;
}

const Vertex Vector::operator * (const double& len)
{
	return Vertex(cos(latency)	* cos (longitude), 0, sin(longitude) * len);
}