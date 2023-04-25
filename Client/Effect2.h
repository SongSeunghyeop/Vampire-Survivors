#pragma once
#include "Effect.h"

namespace my
{
	class Effect2 : public Effect
	{
	public:
		Effect2();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
	};
}

