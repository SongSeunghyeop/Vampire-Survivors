#include "myCollisionManager.h"
#include "myScene.h"
#include "mySceneManager.h"
#include "MyGameObject.h"

namespace my
{
	WORD CollisionManager::mMatrix[(UINT)eLayerType::END] = {}; // ��ü ���̾ �迭�� �����
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Update()
 	{
		Scene* scene = SceneManager::getActiveScene(); // ������ ���� ���� �Ҵ�

 		for (UINT row = 0; row < (UINT)eLayerType::END; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::END; col++) //���� ���� ��ü ���̾�
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
			Collider* leftCollider = leftObject->GetComponent<Collider>(); // ������ ������Ʈ�� �ݶ��̴�
			if (leftCollider == nullptr) // �ݶ��̴��� ���ٸ� 
				continue;

			for (auto rightObject : rights) // �ι�° ������Ʈ�� �ݶ��̴� 
			{
				Collider* rightCollider = rightObject->GetComponent<Collider>();
				if (rightCollider == nullptr)
					continue;

				if (leftObject == rightObject) // �� ������Ʈ�� ���ٸ� 
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

			// ���� �浹 ���������� enter
			if (iter->second == false)
			{
				leftCol->onCollisionEnter(rightCol);
				rightCol->onCollisionEnter(leftCol);

				iter->second = true;
			}
			else // �浹 ���λ��� stay
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
			// ���������� �浹 O
			// ����� �浹 X 
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
		Vector2 leftPos = left->getPos(); // ��ġ�� �޾ƿ� 
		Vector2 rightPos = right->getPos();

		// �� �浹ü ���� �Ÿ���, �������� ���ݳ����� ���� ���ؼ�
		// �Ÿ��� �� ��ٸ� �浹 X, �Ÿ��� �� ª�ٸ� �浹 O
		Vector2 leftSize = left->getSize(); // ũ�� �޾ƿ�
		Vector2 rightSize = right->getSize();

		leftPos.x = leftPos.x + leftSize.x / 2.0f;
		leftPos.y = leftPos.y + leftSize.y / 2.0f;

		rightPos.x = rightPos.x + rightSize.x / 2.0f;
		rightPos.y = rightPos.y + rightSize.y / 2.0f;

		if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f) - 10 // �� ��ü�� �������� �պ��� 
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

