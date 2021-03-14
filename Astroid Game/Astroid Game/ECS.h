#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Manager;
class Component;
class Entity;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T>
ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init()
	{
	}

	virtual void Update()
	{
	}

	virtual void Draw()
	{
	}

	virtual ~Component()
	{
	}
};

class Entity
{
private:
	Manager& _manager;
	bool _active = true;
	std::vector<std::unique_ptr<Component>> _components;

	ComponentArray _componentArray;
	ComponentBitSet _componentBitSet;
	GroupBitSet _groupBitSet;

public:
	Entity(Manager& manager) : _manager(manager) {};
	
	void Update()
	{
		for (std::unique_ptr<Component>& c : _components) c->Update();
	}
	void Draw()
	{
		for (std::unique_ptr<Component>& c : _components) c->Draw();
	}
	bool IsActive() const { return _active; }
	void Destroy() { _active = false; }

	bool HasGroup(Group group)
	{
		return _groupBitSet[group];
	}

	void AddGroup(Group group);
	
	void RemoveGroup(Group group)
	{
		_groupBitSet[group] = false;
	}

	template <typename T> bool HasComponent() const
	{
		return _componentBitSet[GetComponentTypeID<T>];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uniquePtr{ c };
		_components.emplace_back(std::move(uniquePtr));

		_componentArray[GetComponentTypeID<T>()] = c;
		_componentBitSet.set(GetComponentTypeID<T>());
		c->Init();
		return *c;
	}

	template <typename T> T& GetComponent() const
	{
		Component* pointer(_componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(pointer);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> _entities;
	std::array<std::vector<Entity*>, maxGroups> _groupedEntities;

public:
	void Update()
	{
		//std::cout << "All: " <<_entities.size() << " Grouped: " << GetGroup(0).size() + GetGroup(1).size() + GetGroup(2).size() << std::endl;
		for (std::unique_ptr < Entity>& e : _entities) e->Update();
	}

	void Draw()
	{
		for (std::unique_ptr<Entity>& e : _entities) e->Draw();
	}

	void Refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(_groupedEntities[i]);
			v.erase(std::remove_if(v.begin(), v.end(), 
				[i](Entity* entity)
				{
					return !entity->IsActive() || !entity->HasGroup(i);
				}), 
				v.end());
		}
		
		_entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
			[](const std::unique_ptr<Entity>& entity)
			{
				return !entity->IsActive();
			}),
			std::end(_entities));
	}

	Entity& AddEntity()
	{
		Entity* const newEntity = new Entity(*this);
		std::unique_ptr<Entity> uniquePtr{ newEntity };
		_entities.emplace_back(std::move(uniquePtr));

		return *newEntity;
	}

	void AddToGroup(Entity* entity, Group group)
	{
		_groupedEntities[group].emplace_back(entity);
	}

	std::vector<Entity*>& GetGroup(Group group)
	{
		return _groupedEntities[group];
	}

	std::vector<std::unique_ptr<Entity>>& GetEntities()
	{
		return _entities;
	}
};