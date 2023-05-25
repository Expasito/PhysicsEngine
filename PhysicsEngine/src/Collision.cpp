#include "BoxCollider.h"
#include "SphereCollider.h"
/*
* This handles all collisions 
*/
//namespace Collision {
//
//	bool Collided(BoxCollider b1, BoxCollider b2) {
//		glm::vec3 diff = b1.position + b1.lwh - b2.position + b2.lwh;
//		return true;
//	}
//
//	bool Collided(SphereCollider s1, SphereCollider s2) {
//		glm::vec3 diff = s1.position - s2.position;
//		double radiusSum = s1.radius + s2.radius;
//		diff.x = abs(diff.x);
//		diff.y = abs(diff.y);
//		diff.z = abs(diff.z);
//		if (diff.x < radiusSum && diff.y < radiusSum && diff.z < radiusSum) {
//			return true;
//		}
//		return false;
//	}
//}