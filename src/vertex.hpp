#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

class Vertex
{
public:
	Vertex();
	Vertex(const Vertex& v);
	Vertex(double x, double y, double z);
	~Vertex();

	// getters
	const double x() const;
	const double y() const;
	const double z() const;
	
	// setters
	void x(const double& x);
	void y(const double& y);
	void z(const double& z);

	// length
	const double l() const;

	void operator = (const Vertex&);
	void operator += (const Vertex& v);
	void operator -= (const Vertex& v);
	void operator *= (const double& k);
	void operator /= (const double& k);


private:

	double *coord;
};

#endif