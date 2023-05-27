
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

#include <Render/Render.h>

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
	os << vec.x << ' ' << vec.y << ' ' << vec.z;
	return os;
}

namespace Collision {


	bool hasCollided(BoxCollider b1, BoxCollider b2) {
		glm::vec3 diff = b1.position + b1.lwh - b2.position + b2.lwh;
		glm::vec3 dist = b1.lwh + b2.lwh;
		diff.x = abs(diff.x);
		diff.y = abs(diff.y);
		diff.z = abs(diff.z);
		std::cout << "here\n";
		std::cout << diff.x << " " << diff.y << " " << diff.z << "\n";
		std::cout << dist << "\n";
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


/*
* 
*  Testing polymorphism, will be used for Colliders
*/
class Entity {
public:
	int price;
	virtual void print() = 0;
private:
};

class Cow : public Entity {
public:
	Cow() {
		this->price = 5;
	}
	void print() {
		std::cout << "this is a cow\n";
	}
private:
};

class Pig : public Entity {
public:
	Pig() {
		this->price = 5;
	}
	void print() {
		std::cout << "this is a pig\n";
	}
private:
};


void test(Entity* ent) {
	ent->print();
}
int main() {
	Render::init();
	Render::addModel("assets/Sphere.obj", "Sphere");
	
	SphereCollider* a = new SphereCollider();
	a->position = { 0,0,0 };
	a->radius = 1;
	SphereCollider* b = new SphereCollider();
	b->position = { .2,10,0 };
	b->radius = 1;
	while (Render::keepWindow) {
		glm::vec3 forces = { 0,-9.8 * 1 / 1000,0 };
		if (Collision::hasCollided(*a, *b)) {
			forces.y += 9.8*1/1000;
			glm::vec3 dir = glm::normalize(a->position - b->position);
			std::cout << "Dir: " << dir << "\n";
			dir.x *= -9.8 * 1 / 1000.0;
			dir.y *= -9.8 * 1/1000.0;
			dir.z *= -9.8 * 1/1000.0;
			//std::cout << dir << "\n";
			forces += dir;
			std::cout << "Forces: " << forces << "\n";

			

		}
		b->position += forces;
		Render::addInstance("Sphere", b->position, { 0,0,0 }, { 1,1,1 });
		Render::addInstance("Sphere", a->position, { 0,0,0 }, { 1,1,1 });
		Render::renderAll();
		Render::removeInstances("Sphere");
		//std::cout << b->position << "\n";
	}




	//Cow* a = new Cow();
	//Pig* b = new Pig();
	//

	//std::vector<Entity*> ents;

	//ents.push_back(a);
	//ents.push_back(b);

	//for (Entity* e : ents) {
	//	test(e);
	//}

	//Object base;
	//Object move;
	//base.position = { 0,-3,0 };
	//base.collider = BoxCollider({ 0, 0, 0 }, {1,1,1});
	//move.position = { 0,0,0 };
	//move.collider = BoxCollider({ 0,0,0 }, { 1,1,1 });
	//Render::init();

	//Render::addModel("assets/cube.obj", "Cube");

	//Render::addInstance("Cube", {0,0,0}, {0,0,0}, {1,1,1});

	//while (Render::keepWindow) {

	//	Render::removeAllInstances();
	//	Render::addInstance("Cube", base.position, { 0,0,0 }, { 1,1,1 });
	//	Render::addInstance("Cube", move.position, { 0,0,0 }, { 1,1,1 });
	//	Render::renderAll();

	//}
	//Render::exit();
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
