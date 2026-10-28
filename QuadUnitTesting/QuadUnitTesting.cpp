#include "pch.h"
#include "CppUnitTest.h"
#include "raymath.h"
#include "../CDDS_Optimise/Quad.h"
#include "../CDDS_Optimise/GameObject.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuadUnitTesting
{
	TEST_CLASS(QuadUnitTesting)
	{
	public:
		
		TEST_METHOD(TestAABBInit)
		{
			// AABB initialisation value tests
			Vector2 centre = { 2.0f, 1.0f };
			Vector2 halfSize = { 100.0f, 150.0f };

			AABB aabb(centre, halfSize);

			// Ensure expected m_centre initialised values
			Assert::AreEqual(2.0f, aabb.m_centre.x);
			Assert::AreEqual(1.0f, aabb.m_centre.y);
			
			// Ensure expected m_centre initialised values
			Assert::AreEqual(100.0f, aabb.m_halfSize.x);
			Assert::AreEqual(150.0f, aabb.m_halfSize.y);
		}

		TEST_METHOD(TestQuadInit)
		{
			Vector2 centre = { 400.0f, 225.0f };
			Vector2 halfSize = { 400.0f, 225.0f };
			AABB boundary(centre, halfSize);

			Quadtree quad(boundary);

			// Ensure boundary values are equal in boundary and quad objects
			Assert::AreEqual(boundary.m_centre.x, quad.GetBoundary().m_centre.x);
			Assert::AreEqual(boundary.m_centre.y, quad.GetBoundary().m_centre.y);
			Assert::AreEqual(boundary.m_halfSize.x, quad.GetBoundary().m_halfSize.x);
			Assert::AreEqual(boundary.m_halfSize.y, quad.GetBoundary().m_halfSize.y);

			// Ensure pointers are initialised as nullptr
			Assert::IsNull(quad.GetObjects());
			Assert::IsNull(quad.GetChildren());
		}

		TEST_METHOD(TestQuadInsert)
		{
			// Initialise boundary and quadtree object
			Vector2 centre = { 200.0f, 200.0f };
			Vector2 halfSize = { 200.0f, 200.0f };
			AABB boundary(centre, halfSize);
			Quadtree quad(boundary);

			// Create game objects
			GameObject obj1(nullptr, { 100.0f, 100.0f });
			GameObject obj2(nullptr, { 150.0f, 150.0f });
			GameObject obj3(nullptr, { 200.0f, 200.0f });

			// Insert objects into quadtree to capacity
			Assert::IsTrue(quad.Insert(&obj1));
			Assert::IsTrue(quad.Insert(&obj2));

			// At capacity
			// Verify that children are not created yet
			Assert::IsNull(quad.GetChildren());
			Assert::IsNotNull(quad.GetObjects());

			// Insert third object, this should cause subdivide to run
			Assert::IsTrue(quad.Insert(&obj3));

			// Verify that child object was created after subdivision
			Assert::IsNotNull(quad.GetChildren());
			Assert::IsNull(quad.GetObjects());
		}

		TEST_METHOD(TestQuadQuery)
		{
			// Initialise quadtree
			Vector2 centre = { 200.0f, 200.0f };
			Vector2 halfSize = { 200.0f, 200.0f };
			AABB boundary(centre, halfSize);
			Quadtree quad(boundary);

			GameObject obj1(nullptr, { 50.0f, 50.0f });   // Top left region
			GameObject obj2(nullptr, { 350.0f, 50.0f });  // Top right region
			GameObject obj3(nullptr, { 50.0f, 350.0f });  // Bottom left region

			// Insert objects into the quadtree
			quad.Insert(&obj1);
			quad.Insert(&obj2);
			quad.Insert(&obj3);

			// Create query area for top left of the quadtree
			AABB queryArea({ 100.0f, 100.0f }, { 100.0f, 100.0f });
			std::vector<GameObject*> foundObjects;

			// Query the top left quadrant
			quad.Query(queryArea, foundObjects);

			// Only obj 1 should be found since it is in the top left quadrant
			Assert::AreEqual((size_t)1, foundObjects.size());
			Assert::IsTrue(foundObjects[0] == &obj1);
		}
	};
}
