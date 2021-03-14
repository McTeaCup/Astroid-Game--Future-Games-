#include "Collision.h"
#include "Collider.h"

bool Collision::TestCollision(Collider* collA, Collider* collB)
{
	Eigen::Vector2f posA = collA->GetPosition();
	Eigen::Vector2f posB = collB->GetPosition();

	const float distance = sqrtf(powf(posA.x() - posB.x(), 2) + powf(posA.y() - posB.y(), 2));

	return distance <= collA->size + collB->size;
}
