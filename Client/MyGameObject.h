#pragma once
#include "myEntity.h"
#include "myComponent.h"

namespace my
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			None,
			Death,
		};

		GameObject();
		virtual ~GameObject();

	    virtual void Initialize();
	    virtual void Update();
	    virtual void Render(HDC hdc);
	    virtual void Release();

		virtual void onCollisionEnter(class Collider* other);
		virtual void onCollisionStay(class Collider* other);
		virtual void onCollisionExit(class Collider* other);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T(); // 들어온 컴포넌트의 자식 클래스로 동적 할당
			UINT compType = (UINT) comp->getType();	// getType() = 컴포넌트 타입(Enum class) 반환
			mComponents[compType] = comp; // 컴포넌츠배열에 그 타입의 객체 삽입
			comp->setOwner(this);
			return comp; // 동적할당된 객체 리턴
		}
		template <typename T>
		T* GetComponent()
		{
			for (Component* c : mComponents) // 컴포넌트 배열을 찾아보면서
			{
				if (dynamic_cast<T*>(c)) // 만약 그 클래스 타입이 발견된다면, 
					return dynamic_cast<T*>(c); // 그 클래스 타입으로 형변환해서 반환
			}
				return NULL;
		}

		eState getState() { return mState; }
		void setState(eState state) { mState = state; }


	private:
		std::vector<Component*> mComponents;
		eState mState;
	};
}


