#include "ODESolver.h"
#include <iostream>

ODESolver::ODESolver() {

}

void ODESolver::add2yForce(double force) {
	d2y_values.push_back(force);
}

void ODESolver::add1yForce(double force) {
	d1y_values.push_back(force);
}

void ODESolver::add0yForce(double force) {
	d0y_values.push_back(force);
}

void ODESolver::addconstForce(double force) {
	const_values.push_back(force);
}


void ODESolver::solve() {
	// these are the constants in front of each derrivative
	double d2y_value = 0;
	double d1y_value = 0;
	double d0y_value = 0;
	double const_value = 0;
	for (double d : d2y_values) {
		d2y_value += d;
	}
	for (double d : d1y_values) {
		d1y_value += d;
	}
	for (double d : d0y_values) {
		d0y_value += d;
	}
	for (double d : const_values) {
		const_value += d;
	}

	// 3 cases, d2y!=0 so no double d values
	if (d2y_value != 0) {
		y2 = (-d1y_value * y1 - d0y_value * y0 - const_value) / d2y_value;
		y1 += dt * y2;
		y0 += y1 * dt;
	}
	else if (d1y_value != 0) {
		y1 = (-d0y_value * y0 - const_value) / d1y_value;
		y0 += dt * y1;
	}
	else if (d0y_value != 0) {
		y0 = -const_value / d0y_value;
	}
	else {
		y0 = - const_value;
	}
	


	
}