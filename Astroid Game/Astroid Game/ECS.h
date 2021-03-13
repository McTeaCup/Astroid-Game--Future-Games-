#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T>
ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
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
	bool _active = true;
	std::vector<std::unique_ptr<Component>> _components;

	ComponentArray _componentArray;
	ComponentBitSet _componentBitSet;

public:
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

public:
	void Update()
	{
		for (std::unique_ptr < Entity>& e : _entities) e->Update();
	}

	void Draw()
	{
		for (std::unique_ptr<Entity>& e : _entities) e->Draw();
	}

	void Refresh()
	{
		_entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(_entities));
	}

	Entity& AddEntity()
	{
		Entity* const newEntity = new Entity();
		std::unique_ptr<Entity> uniquePtr{ newEntity };
		_entities.emplace_back(std::move(uniquePtr));

		return *newEntity;
	}

	std::vector<std::unique_ptr<Entity>>* GetEntities()
	{
		return &_entities;
	}
};