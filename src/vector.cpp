#include <math.h>
#include "vector.hpp"

const double Vector::PI = acos(-1);

Vector::Vector() : latency(0), longitude(0), rotation(0)
{

}

Vector::Vector(double lon, double lat, double rot) : latency(lon), longitude(lat), rotation(rot)
{
	// TODO: avoid huge numbers
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

double& Vector::lon()
{
	return latency;
}

double& Vector::lat()
{
	return longitude;
}

double& Vector::rot()
{
	return rotation;
}

void Vector::lon(const double& lon)
{
	latency = lon;
}

void Vector::lat(const double& lat)
{
	longitude = lat;
}

void Vector::rot(const double& rot)
{
	rotation = rot;
}

const Vertex Vector::operator * (const double& len) const
{
	return Vertex(cos(latency) * cos(longitude) * len, sin(latency) * cos (longitude) * len, sin(longitude) * len);
}

const Vector Vector::operator - () const
{
	return Vector(latency + PI, -longitude, -rotation);
}

void Vector::operator += (const Vector& v)
{
	latency += v.latency;
	longitude += v.longitude;
	rotation += v.rotation;
}
