#include "pch.h"
#include "CppUnitTest.h"
#include "raymath.h"
#include "../CDDS_Optimise/Quad.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuadUnitTesting
{
	TEST_CLASS(QuadUnitTesting)
	{
	public:
		
		TEST_METHOD(TestQuadInit)
		{
			// TODO: Unit tests
			Vector2 centre = { 2, 1 };
			Vector2 halfSize = { 1, 1 };

			AABB aabb(centre, halfSize);

			Assert::AreEqual(2.0f, aabb.m_centre.x);
		}
	};
}
