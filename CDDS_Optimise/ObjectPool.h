#pragma once

#include <vector>
#include "Critter.h"

class ObjectPool
{
private:
	std::vector<Critter> m_pool;

public:
	ObjectPool(size_t poolSize) {
		// pre-allocate space in stack
		m_pool.resize(poolSize);
	}

	// grab inactive critter from pool
	Critter* Spawn(Vector2 position, Vector2 velocity, float radius, Texture2D* texture) {
		for (auto& critter : m_pool) {
			if (critter.IsDead()) {
				critter.Init(position, velocity, radius, texture);
				return &critter; // return pointer to newly active critter
			}
		}
		return nullptr; // pool full
	}

	std::vector<Critter>& GetPool() {
		return m_pool;
	}
};
