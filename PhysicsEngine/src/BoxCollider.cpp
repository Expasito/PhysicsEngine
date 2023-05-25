#include "BoxCollider.h"

BoxCollider::BoxCollider() {
	position = { 0,0,0 };
	lwh = { 1,1,1 };
}

BoxCollider::BoxCollider(glm::vec3 pos, glm::vec3 lenwidhei) {
	position = pos;
	lwh = lenwidhei;
}