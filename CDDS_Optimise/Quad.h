#pragma once

#include "raymath.h"
#include <vector>

class GameObject;

class AABB
{
public:
    AABB() {}
    AABB(Vector2 centre, Vector2 halfSize) : m_centre(centre), m_halfSize(halfSize) {}

    bool contains(Vector2 point) {
        if (point.x >= m_centre.x - m_halfSize.x &&
            point.x <= m_centre.x + m_halfSize.x &&
            point.y >= m_centre.y - m_halfSize.y &&
            point.y <= m_centre.y + m_halfSize.y)
            return true;
        return false;
    }

    bool intersects(AABB other) {
        // if this box's right edge is < other box's left
        if (m_centre.x + m_halfSize.x < other.m_centre.x - other.m_halfSize.x ||
            // or this box's left edge is > other box's right
            m_centre.x - m_halfSize.x > other.m_centre.x + other.m_halfSize.x ||
            // or this box's top edge is < other box's bottom
            m_centre.y + m_halfSize.y < other.m_centre.y - other.m_halfSize.y ||
            // or this box's bottom edge is > other box's top
            m_centre.y - m_halfSize.y > other.m_centre.y + other.m_halfSize.y)
            // then they can't possibly be intersecting
            return false;
        return true;
    }
    Vector2 m_centre;
    Vector2 m_halfSize;
};

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
    void Query(AABB area, std::vector<GameObject*>& foundObjects);

private:
    Quadtree** m_children;
    AABB m_boundary;
    GameObject** m_objects;
};

