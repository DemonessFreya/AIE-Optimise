#include "GameObject.h"

GameObject::GameObject(Texture2D* texture, Vector2 position) {
	m_texture = texture;

	m_bounds.m_centre = position;
	if (m_texture != nullptr) {
		m_bounds.m_halfSize.x = m_texture->width >> 1;
		m_bounds.m_halfSize.y = m_texture->height >> 1;
	} else {
		m_bounds.m_halfSize = Vector2{ 0, 0 };
	}
}

GameObject::~GameObject() {}

void GameObject::Update(float delta) {}

void GameObject::Draw() {
	if (m_texture != nullptr) {
		DrawTexture(*m_texture, m_bounds.m_centre.x, m_bounds.m_centre.y, WHITE);
	}
}