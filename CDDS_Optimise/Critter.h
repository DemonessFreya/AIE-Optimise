#pragma once

#include "raylib.h"
#include "GameObject.h"

class Critter : public GameObject
{
protected:
	Vector2 m_velocity;
	float m_radius;

	bool m_isLoaded;
	bool m_isDirty;		// indicates if we've already processed a collision response for this critter
	
public:
	Critter();
	~Critter();

	void Init(Vector2 position, Vector2 velocity, float radius, Texture2D* texture);
	void Destroy();
	void Update(float dt);
	void Draw();

	float GetX() { return m_bounds.m_centre.x; }
	float GetY() { return m_bounds.m_centre.y; }
	void SetX(float x) { m_bounds.m_centre.x = x; }
	void SetY(float y) { m_bounds.m_centre.y = y; }

	Vector2 GetPosition() { return m_bounds.m_centre; }
	void SetPosition(Vector2 position) { m_bounds.m_centre = position; }

	Vector2 GetVelocity() { return m_velocity; }
	void SetVelocity(Vector2 velocity) { m_velocity = velocity; }

	float GetRadius() { return m_radius; }

	bool IsDirty() { return m_isDirty; }
	void SetDirty() { m_isDirty = true; }

	bool IsDead() { return m_isLoaded == false; }

};
