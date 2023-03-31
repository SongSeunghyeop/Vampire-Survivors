#pragma once
#include "Krochi.h"
#include "Enemy.h"

namespace my
{
	class Radar: public Krochi
	{
	public:
		Radar();
		~Radar();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void onCollisionStay(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionEnter(class Collider* other) override;

		static Vector2 getEnemyPos() { return Enemy_Pos; }
	private:
		Collider* radar_Collider;
		Transform* rader_Tr;
		Vector2 Radar_Size;
		

		static Vector2 Enemy_Pos;

		friend class Krochi;
	};
}

