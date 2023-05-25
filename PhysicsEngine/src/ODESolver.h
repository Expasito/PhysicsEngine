#pragma once
#include <vector>
class ODESolver
{
public:
	

	ODESolver();
	void add2yForce(double);
	void add1yForce(double);
	void add0yForce(double);
	void addconstForce(double);

	double y0 = 0;
	double y1 = 0;
	double y2 = 0;

	double dt = .1;

	void solve();




private:
	std::vector<double> d2y_values;
	std::vector<double> d1y_values;
	std::vector<double> d0y_values;
	std::vector<double> const_values;

	
};

