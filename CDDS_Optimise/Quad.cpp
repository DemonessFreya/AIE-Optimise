#include "Quad.h"

class GameObject;

class Quadtree
{
public:
	static const int m_capacity = 2;

	enum SUBTREE {
		TOP_LEFT = 0,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

public:
	Quadtree();
	Quadtree(AABB boundary);
	~Quadtree();

	bool Insert(GameObject*);
	void Subdivide();

	void Update(float delta);
	void Draw();

private:
	Quadtree** m_children;
	AABB m_boundary;
	GameObject** m_objects;
};

Quadtree::Quadtree() : m_objects(nullptr), m_children(nullptr) {
	m_boundary.m_halfSize.x = 800 / 2;
	m_boundary.m_halfSize.y = 450 / 2;
	m_boundary.m_centre = m_boundary.m_halfSize;
}

Quadtree::Quadtree(AABB boundary) : m_boundary(boundary), m_objects(nullptr), m_children(nullptr) {}

Quadtree::~Quadtree() {
	if (m_children != nullptr) {
		for (int i = 0; i < 4; i++) {
			if (m_children[i] != nullptr) delete m_children[i];
		}
		delete m_children;
		m_children = nullptr;
	}

	if (m_objects != nullptr) {
		for (int i = 0; i < m_capacity; i++) {
			if (m_objects[i] != nullptr) delete m_objects[i];
		}
		delete m_objects;
		m_objects = nullptr;
	}
}
