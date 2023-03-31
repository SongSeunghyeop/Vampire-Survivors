#pragma once
#include "myComponent.h"

namespace my
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void setPos(Vector2 pos);
		void setPos(int a, int b);
		void setScale(Vector2 scale);
		void setScale(float a, float b);

		Vector2 getPos();
		Vector2 getScale();

	private:
		Vector2 mPos;
		Vector2 mScale;
	};
}

