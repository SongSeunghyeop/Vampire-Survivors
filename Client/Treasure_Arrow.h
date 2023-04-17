#pragma once
#include "Treasure.h"
namespace my
{
	class Treasure_Arrow : public GameObject
	{
	public:
		Treasure_Arrow();
		~Treasure_Arrow();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		void SetTreasure(Treasure* t) { treasure = t; }
	private:
		Transform* arrow_Tr;
		Vector2* arrowPos;
		Image* Arrow_D;
		Image* Arrow_U;
		Image* Arrow_R;
		Image* Arrow_L;
		Image* trea;
		Animator* trea_animator;
		Treasure* treasure;
	};
}

