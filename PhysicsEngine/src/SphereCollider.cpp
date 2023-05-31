#include "SphereCollider.h"

SphereCollider::SphereCollider() {
	position = { 0.0,0.0,0.0 };
	radius = 1.0;
	velocity = { 0.0,0.0,0.0 };
	acceleration = { 0.0,0.0,0.0 };
	mass = 1.0;
}

SphereCollider::SphereCollider(glm::vec3 pos, double rad) {
	position = pos;
	radius = rad;
	velocity = { 0.0,0.0,0.0 };
	acceleration = { 0.0,0.0,0.0 };
	mass = 1.0;
}