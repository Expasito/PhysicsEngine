
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
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread>
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
		std::cout << diff.x << " " << diff.y << " " << diff.z << "\n";
		std::cout << dist << "\n";
		if (diff.x < dist.x && diff.y < dist.y && diff.z < dist.z) {
			return true;
		}
		return false;
	}

	bool hasCollided(SphereCollider s1, SphereCollider s2) {
		glm::vec3 diff = s2.position - s1.position;
		double radiusSum = (s2.radius + s1.radius);
		float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
		//std::cout << "Dist "<<dist << "\n";
		//diff.x = abs(diff.x);
		//diff.y = abs(diff.y);
		//diff.z = abs(diff.z);
		return dist < radiusSum;
		//if (diff.x < radiusSum && diff.y < radiusSum && diff.z < radiusSum) {
		//	return true;
		//}
		//return false;
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

float sgn(float x) {
	if (x > 0) {
		return 1;
	}
	else if (x < 0) {
		return -1;
	}
	else {
		return 0;
	}
}


void test(Entity* ent) {
	ent->print();
}
int main() {
	Render::init();
	Render::addModel("assets/Sphere.obj", "Sphere");
	
	SphereCollider* a = new SphereCollider({-1.0,1.0,0.0},1.0);

	SphereCollider* b = new SphereCollider({0.0,10.0,0.0},1.0);

	SphereCollider* c = new SphereCollider({1.0,0.0,0.0}, 1.0);

	std::vector<SphereCollider*> spheres;
	//spheres.push_back(a);
	//spheres.push_back(b);
	//spheres.push_back(c);
	//spheres.push_back(new SphereCollider({ 4.0,1.0,0.0 }, 1));
	//spheres.push_back(new SphereCollider({ 2.0,5.0,0.0 }, 1));
	//spheres.push_back(new SphereCollider({ -5.0,15.0,0.0 }, 1));

	//spheres.push_back(new SphereCollider({ 2.0,7.0,0.0 }, 1));
	//spheres.push_back(new SphereCollider({ 0.1,1.0,0.0 }, 1));
	spheres.push_back(new SphereCollider({ 1.1,5.0,0.0 }, 1));
	//for (int i = 0; i < 15; i++) {
	//	spheres.push_back(new SphereCollider({ 0.0,(double)(i*2+5),0.0}, 1));
	//}

	double framerate = 120.0;

	float timestep = 1.0 / 256;
	double cor = 1;
	float milis=16.6;

	while (Render::keepWindow) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		//timestep = 1.0 / framerate/10.0;
		


		
		for (int i = 0; i < 256/framerate; i++) {
			//std::cout << "iteration\n";
			for (SphereCollider* sc : spheres) {
				// already account for gravity
				glm::vec3 forces = { 0,-9.8,0 };
				for (SphereCollider* sc2 : spheres) {
					if (sc == sc2) {
						continue;
					}

					if (Collision::hasCollided(*sc, *sc2)) {
						//forces.y += 9.8*1/1000

						//forces += -bvel;

						//std::cout << sc->position << "   " << sc2->position << "\n";

						glm::vec3 dir = glm::normalize(sc->position - sc2->position);
						glm::vec3 dir2 = glm::normalize(sc->position - sc2->position);
						//std::cout << "Dir: " << dir << "\n";
						//std::cout << "Dir2: " << glm::normalize(sc2->position - sc->position) << "\n";
						//dir.x = 0;
						double angle = -(atan(dir.x / dir.y) * 180.0 / M_PI);
						std::cout << dir << "\n";
						std::cout << "Angle: " << angle << "\n";
						std::cout << "vel: " << sc->velocity << "\n";
						std::cout << "Angle2: " << atan(sc->velocity.x / sc->velocity.y) << "\n";
						int a;
						std::cin >> a;

						dir.z = 0;
						dir.x = sin(angle * M_PI / 180.0) * -9.8;
						dir.y = -cos(angle * M_PI / 180.0) * -9.8;

						double x1a = (sc->mass - cor * sc2->mass) * sc->velocity.x / (sc->mass + sc2->mass) +
							(1 + cor) * sc2->mass * sc2->velocity.x / (sc->mass + sc2->mass);

						double x2a = (1 + cor) * sc->mass * sc->velocity.x / (sc->mass + sc2->mass) +
							(sc2->mass - cor * sc->mass) * sc2->velocity.x / (sc->mass + sc2->mass);

						dir.x = sin(angle * M_PI / 180.0) * sc2->velocity.y;
						dir.y = -cos(angle * M_PI / 180.0) * sc2->velocity.y;
						//std::cout << "Dir2: " << dir << "\n";
						//dir.z = -9.8 * 1/1000.0;
						//std::cout << dir << "\n";
						//std::cout << "Forces1: " << forces << "\n";
						//dir.x = 0;
						dir.x *= sgn(dir2.x)*-sgn(angle);
						dir.y *= sgn(dir2.y);
						//forces.x *= sgn(dir.x);
						//forces.y *= sgn(dir.y);
						//forces.z *= sgn(dir.z);
						forces += dir;
						//std::cout << "Forces: " << forces << "\n";




					}

					//if (sc->position.y <= 0) {
					//	std::cout << "lower\n";
					//	forces.y += 9.5;
					//}
					
					
					//if (fabs(sc->position.x - 5) > 0) {
					//	sc->position.x = 5;
					//}

				}
				//std::cout << "Forces: " << forces << "\n";
				//std::cout << sc->position.y << "\n";
				if (sc->position.y <= 0) {
					//forces.y += 9.8;
					forces.y += 1 * -2*(sc->velocity.y) / timestep;
					//sc->position.y = 0;
				}
				if (sc->position.x > 10) {
					forces.x += 1 * -2*(sc->velocity.x) / timestep;
				}
				if (sc->position.x < -10) {
					forces.x += 1 * -2 * (sc->velocity.x) / timestep;
				}

				std::cout << "Forces1: " << forces << "\n";
				//if (sc->position.x < -3) {
				//	forces.x += abs(sc->velocity.x);
				//}

				//forces.x *= .99;
				//forces.y *= .99;
				//forces.z *= .99;
				sc->acceleration = forces;
				sc->velocity += sc->acceleration * timestep;
				sc->position += sc->velocity * timestep;
			}
			

		}
		for (SphereCollider* sc : spheres) {
			Render::addInstance("Sphere", sc->position, { 0,0,0 }, { sc->radius,sc->radius,sc->radius });
		}
		
		
		Render::renderAll();
		Render::removeInstances("Sphere");
		//std::cout << b->position << "\n";

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		milis = (end - begin).count() / 1000000.0;
		std::cout << "Time difference = " << milis << "[ms]" << " FPS: " << 1000.0 / milis << "\n";
		// this sets the frame rate
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / framerate - milis)));
		
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
