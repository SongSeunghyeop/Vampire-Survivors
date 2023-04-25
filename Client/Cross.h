#pragma once
#include "Skillmanager.h"

namespace my
{
	class Cross : public SkillManager
	{
	public:
		Cross();
		~Cross();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	private:
	};
}
