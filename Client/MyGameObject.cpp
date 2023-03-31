#include "myGameObject.h"
#include "myTransform.h"

namespace my
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		mComponents.resize((UINT)eComponentType::END);
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* mcomp : mComponents)
		{
			if (mcomp == NULL) continue;

			mcomp->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* mcomp : mComponents)
		{
			if (mcomp == NULL) continue;

				mcomp->Update();
		}
	}
	void GameObject::Render(HDC hdc)
	{
		for (Component* mcomp : mComponents)
		{
			if (mcomp == NULL) continue;

			mcomp->Render(hdc);
		}
	}
	void GameObject::Release()
	{
		for (Component* mcomp : mComponents)
		{
			if (mcomp == NULL) continue;

			mcomp->Release();
		}
	}

	void GameObject::onCollisionEnter(Collider* other)
	{

	}
	void GameObject::onCollisionStay(Collider* other)
	{

	}
	void GameObject::onCollisionExit(Collider* other)
	{

	}
}
