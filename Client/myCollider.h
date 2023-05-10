#pragma once
#include "myComponent.h"
#include "myCamera.h"
#include "myInput.h"

namespace my
{
	class Collider : public Component
	{
	public:
		Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void onCollisionEnter(Collider* other);
		virtual void onCollisionStay(Collider* other);
		virtual void onCollisionExit(Collider* other);

		void setCenter(Vector2 center) { mCenter = center; };
		void setSize(Vector2 size) { mSize = size; };
		void setRGB(int r, int g, int b) { mRgb.r = r; mRgb.g = g; mRgb.b = b; };
		void setPos(Vector2 pos) { mPos = pos; };

		Vector2 getPos() { return mPos; }
		Vector2 getSize() { return mSize; }
		UINT getID() { return mID; }

	private:
		static UINT ColliderNumber;
		UINT mID;
		Vector2 mCenter;
		Vector2 mSize;
		Vector2 mPos;
		MyRGB mRgb;

		static bool collider_on;
	};
}
