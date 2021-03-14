#include "ECS.h"

void Entity::AddGroup(Group group)
{
	_groupBitSet[group] = true;
	_manager.AddToGroup(this, group);
}