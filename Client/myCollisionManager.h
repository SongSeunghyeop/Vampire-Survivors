#pragma once
#include "CommonInclude.h"
#include "Enum.h"
#include "myCollider.h"

namespace my
{
	union ColliderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};

	class Scene;
	class CollisionManager
	{
	public:
		static void Update();
		static void LayerCollision(Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider* leftCol, Collider* rightCol, eLayerType left, eLayerType right);
		static bool Intersect(Collider* left, Collider* right);

		static void setLayer(eLayerType left, eLayerType right, bool value);
		static void clear();

	private:
		static WORD mMatrix[(UINT)eLayerType::END];
		static std::map<UINT64, bool> mCollisionMap;
	};
}
