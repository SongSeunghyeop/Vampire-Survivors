#pragma once
#include "Skillmanager.h"

namespace my
{
	class Ax1 : public SkillManager
	{
	public:
		Ax1();
		~Ax1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void setVel(float v) override {
			Ax_vel_X = v;  Ax_vel_Y = v;
		}
	private:
		float Ax_vel_X;
		float Ax_vel_Y;
	};
}
