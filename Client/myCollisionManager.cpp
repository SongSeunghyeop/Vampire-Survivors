#include "myCollisionManager.h"
#include "myScene.h"
#include "mySceneManager.h"
#include "MyGameObject.h"

namespace my
{
	WORD CollisionManager::mMatrix[(UINT)eLayerType::END] = {}; // 전체 레이어를 배열로 만든다
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Update()
 	{
		Scene* scene = SceneManager::getActiveScene(); // 현재의 씬을 동적 할당

 		for (UINT row = 0; row < (UINT)eLayerType::END; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::END; col++) //현재 씬의 전체 레이어
			{
				if (mMatrix[row] & (1 << col)) 
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
 			}
		}
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		std::vector<GameObject*>& lefts = scene->GetGameObj(left);
		std::vector<GameObject*>& rights = scene->GetGameObj(right);

		for (auto leftObject : lefts)
		{
			Collider* leftCollider = leftObject->GetComponent<Collider>(); // 현재의 오브젝트의 콜라이더
			if (leftCollider == nullptr) // 콜라이더가 없다면 
				continue;

			for (auto rightObject : rights) // 두번째 오브젝트의 콜라이더 
			{
				Collider* rightCollider = rightObject->GetComponent<Collider>();
				if (rightCollider == nullptr)
					continue;

				if (leftObject == rightObject) // 두 오브젝트가 같다면 
					continue;
			

				ColliderCollision(leftCollider, rightCollider, left, right);
			}

		}
	}

	void CollisionManager::ColliderCollision(Collider* leftCol, Collider* rightCol, eLayerType left, eLayerType right)
	{
		ColliderID colliderID = {};
		colliderID.left = (UINT)leftCol->GetID();
		colliderID.right = (UINT)rightCol->GetID();

		//static std::map<UINT64, bool> mCollisionMap;
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(colliderID.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		if (Intersect(leftCol, rightCol))
		{

			// 최초 충돌 시작했을때 enter
			if (iter->second == false)
			{
				leftCol->onCollisionEnter(rightCol);
				rightCol->onCollisionEnter(leftCol);

				iter->second = true;
			}
			else // 충돌 중인상태 stay
			{
				leftCol->onCollisionStay(rightCol);
				rightCol->onCollisionStay(leftCol);
			}
			/////
		/*	if (leftCol->getOwner()->getState() == GameObject::eState::Death ||
				rightCol->getOwner()->getState() == GameObject::eState::Death)
			{
				leftCol->onCollisionExit(rightCol);
				rightCol->onCollisionExit(leftCol);
			}*/
			////
		}
		else
		{
			// Exit
			// 이전프레임 충돌 O
			// 현재는 충돌 X 
			if (iter->second == true)
			{
				leftCol->onCollisionExit(rightCol);
				rightCol->onCollisionExit(leftCol);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->getPos(); // 위치를 받아옴 
		Vector2 rightPos = right->getPos();

		// 두 충돌체 간의 거리와, 각면적의 절반끼리의 합을 비교해서
		// 거리가 더 길다면 충돌 X, 거리가 더 짧다면 충돌 O
		Vector2 leftSize = left->getSize(); // 크기 받아옴
		Vector2 rightSize = right->getSize();

		leftPos.x = leftPos.x + leftSize.x / 2.0f;
		leftPos.y = leftPos.y + leftSize.y / 2.0f;

		rightPos.x = rightPos.x + rightSize.x / 2.0f;
		rightPos.y = rightPos.y + rightSize.y / 2.0f;

		if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f) - 10 // 두 객체의 반지름의 합보다 
			&& fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f) - 10)
		{
			return true;
		}
		return false;
	}

	void CollisionManager::setLayer(eLayerType left, eLayerType right, bool value)
	{
		UINT row = 0;
		UINT col = 0;

		UINT ileft = (UINT)left;
		UINT iright = (UINT)right;  

		if (left <= right)
		{
			row = ileft;
			col = iright;
		}
		else if(left >= right)
		{
			row = iright;
			col = ileft;
		}
		else
		{
			row = ileft;
			col = ileft;
		}

		if (value == true)
			mMatrix[row] |= (1 << col);

		else
			mMatrix[row] &= ~(1 << col);
	}

	void CollisionManager::clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * (UINT)eLayerType::END);
		mCollisionMap.clear();
	}
}

