#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

class Vector;

#include "vertex.hpp"

class Vector
{
public:
	Vector();
	Vector(double latency, double longitude, double rotation);
	Vector(const Vector& v);
	Vector(const Vertex& v);
	~Vector();

	double& lat();
	double& lon();
	double& rot();

	void lat(const double& lat);
	void lon(const double& lon);
	void rot(const double& rot);

	const Vertex operator * (const double& len) const;
	const Vector operator - () const;
	void operator += (const Vector& v);

private:

	double latency;
	double longitude;
	double rotation;
	static const double PI;
};

#endif