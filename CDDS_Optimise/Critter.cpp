#include "Critter.h"


Critter::Critter() : GameObject(nullptr, Vector2{0,0})
{
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
	m_isLoaded = false;
	m_isDirty = false;
}

Critter::~Critter()
{
	m_isLoaded = false;
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, Texture2D* texture)
{
	m_texture = texture;
	m_bounds.m_centre = position;
	m_bounds.m_halfSize = Vector2{ radius, radius };

	m_velocity = velocity;
	m_radius = radius;
	m_isLoaded = true;
}

void Critter::Destroy()
{
	m_isLoaded = false;
}

void Critter::Update(float dt)
{
	if (m_isLoaded == false) return;

	m_bounds.m_centre.x += m_velocity.x * dt;
	m_bounds.m_centre.y += m_velocity.y * dt;

	m_isDirty = false;
}

void Critter::Draw()
{
	// if the critter is dead, don't draw it
	if (!m_isLoaded) return;

	// call base class GameObject draw logic
	GameObject::Draw();
}
