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
	double& x() const;
	double& y() const;
	double& z() const;
	
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