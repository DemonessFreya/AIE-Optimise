#pragma once

#include "Quad.h"

class GameObject
{
public:
	GameObject(Texture2D* m_texture, Vector2 position);
	~GameObject();

	void Update(float delta);
	void Draw();

	Texture2D* m_texture;
	AABB m_bounds;
};
