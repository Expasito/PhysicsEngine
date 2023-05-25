
#include <iostream>
#include <math.h>
#include <vector>
#include <glm/vec3.hpp>
#include "ODESolver.h"
#include "Container.h"
#include "Object.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include <string>
//#include "Collision.cpp"

namespace Collision {

	bool hasCollided(BoxCollider b1, BoxCollider b2) {
		glm::vec3 diff = b1.position + b1.lwh - b2.position + b2.lwh;
		glm::vec3 dist = b1.lwh + b2.lwh;
		diff.x = abs(diff.x);
		diff.y = abs(diff.y);
		diff.z = abs(diff.z);
		if (diff.x < dist.x && diff.y < dist.y && diff.z < dist.z) {
			return true;
		}
		return false;
	}

	bool hasCollided(SphereCollider s1, SphereCollider s2) {
		glm::vec3 diff = s2.position - s1.position;
		double radiusSum = s2.radius + s1.radius;
		diff.x = abs(diff.x);
		diff.y = abs(diff.y);
		diff.z = abs(diff.z);
		if (diff.x < radiusSum && diff.y < radiusSum && diff.z < radiusSum) {
			return true;
		}
		return false;
	}

	glm::vec3 direction(SphereCollider s1, SphereCollider s2) {
		return s2.position - s1.position;
	}
}



struct Point {
	double x;
	double y;
};

struct Force {
	Point p;
	double magnitude;
};

struct Circle {
	Point center;
	double radius;
	Force force;
	double mass;
	Point velocity;

};

Circle* createCircle(double x, double y, double radius) {
	Circle* c = (Circle*)malloc(sizeof(Circle));
	c->center = { x,y };
	c->velocity = { 0,2 };
	c->radius = radius;
	c->mass = 1;
	return c;
}

void printCircle(Circle* circle) {
	std::cout << "Circle(x=" << circle->center.x << ", y=" << circle->center.y << ", vx=" << circle->velocity.x << ", vy=" << circle->velocity.y << ", ax=" << circle->force.p.x << ", ay=" << circle->force.p.y << ")\n";
}

void constraint(Circle* circle) {
	if (circle->center.y < 0) {
		circle->center.y = 0;
		//circle->velocity.y = 0;
	}
}

void step(Circle* circle) {
	double timestep = 1/100.0;
	circle->force.p.x = 0;
	circle->force.p.y = 0;
	// sum up all forces
	circle->force.p.y +=
		-9.8 * circle->mass;
		//+ .01*circle->velocity.y*circle->velocity.y;
	//if (circle->center.y < 0) {
	//	circle->force.p.y += -circle->mass * circle->velocity.y / 2 * timestep;
	//}

	// this is a collision with y=0
	if (circle->center.y < 0) {
		//add normal force
		circle->force.p.y += 9.8;
		//impact force
		//circle->force.p.y += -circle->mass * circle->velocity.y / 2 * (-9.8 * 2 / circle->velocity.y);
		// cancel out velocity
		//circle->force.p.y += -circle->velocity.y * 1 / timestep;
		circle->force.p.y += -circle->velocity.y / timestep;
	}
	circle->force.p.x += 0;

	circle->velocity.x += circle->force.p.x * timestep / circle->mass;
	circle->velocity.y += circle->force.p.y * timestep / circle->mass;
	circle->center.x += circle->velocity.x * timestep;
	circle->center.y += circle->velocity.y * timestep;
	//if (circle->center.y < 0) {
	//	circle->center.y = 0;
	//}
	//constraint(circle);
	
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
	os << vec.x << ' ' << vec.y << ' ' << vec.z;
	return os;
}
std::vector<std::string> strsplit(std::string str, char dem) {
	std::vector<std::string> strs;
	//std::vector<std::string>* strs = new std::vector<std::string>();
	while (str.size() != 0) {
		std::cout << str << "\n";
		
		size_t pos = str.find(dem);
		std::cout << "pos: " << pos << "\n";
		// dem does exist
		if (pos != std::string::npos) {
			std::string temp = str.substr(0, pos);
			strs.push_back(temp);
			str.erase(0, pos+1);
		}
		else {
			std::string temp = str;
			strs.push_back(temp);
			break;
		}
	}
	return strs;
}
int main() {
	std::vector<std::string> s = strsplit("hello hi hye, h", 'h');
	//std::vector<std::string> s2 = *s;
	std::cout << "final\n\n";
	for (std::string c : s) {
		std::cout << c << "\n";
	}
	//Container c;
	//c.addChild(new Object({ 0,1,0 }, { 0,0,0 }));
	//SphereCollider s1({0,0,0}, 1);
	//SphereCollider s2({ 1,1,1 }, 1);
	//std::cout << "Collided: " << Collision::hasCollided(s1, s2);
	//std::cout << "\nCollided: " << Collision::hasCollided(s2, s1);

	//std::cout << "\nDir: " << Collision::direction(s1, s2);

	/*std::vector<Circle*> circles;
	circles.push_back(createCircle(0,1,1));
	printCircle(circles[0]);
	for (int i = 0; i < 100000;i++) {
		step(circles[0]);
		printCircle(circles[0]);
	}

	auto lam = [](int x, int y) -> int
	{return x + y; };

	std::cout << lam(1,1) << "\n";*/

	//ODESolver ode;
	//ode.add2yForce(1);
	//ode.add1yForce(-.1);
	//ode.add0yForce(0);
	//ode.addconstForce(1);
	//ode.y0 = 5;
	//ode.y1 = 0;
	//for (int i = 0; i < 1000; i++) {
	//	std::cout << ode.y2 << " " <<ode.y1 << " " << ode.y0 << "\n";
	//	ode.solve();
	//}
	


}
