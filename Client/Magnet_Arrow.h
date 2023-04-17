#pragma once
#include "Magnet.h"
namespace my
{
	class Magnet_Arrow : public GameObject
	{
	public:
		Magnet_Arrow();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		void SetMagnet(Magnet* m) { magnet = m; }
	private:
		Transform* arrow_Tr;
		Vector2* arrowPos;
		Image* Arrow_D;
		Image* Arrow_U;
		Image* Arrow_R;
		Image* Arrow_L;
		Image* mag;
		Animator* mag_animator;
		Magnet* magnet;
	};
}

