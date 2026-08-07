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
		// offset texture by half its width and height to centre the texture on its hitbox (m_bounds.m_centre)
		float offsetX = (float)m_texture->width / 2.0f;
		float offsetY = (float)m_texture->height / 2.0f;

		DrawTexture(*m_texture,
			(int)(m_bounds.m_centre.x - offsetX),
			(int)(m_bounds.m_centre.y - offsetY),
			WHITE);
	}
}