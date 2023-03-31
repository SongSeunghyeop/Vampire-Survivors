#pragma once
#include "myResourceManager.h"
#include "myGameObject.h"
#include "myImage.h" 
#include "krochi.h"

namespace my
{
	class LevelManager : public GameObject
	{
	public:
		enum class eItems
		{
			WIND,
			BLADE,
			POWER_UP,
			LIGHTNING,
			NONE,
		};

		LevelManager();
		~LevelManager();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void speed_up();
		void blade_up();
		void light_up();
		void power_up();

		static bool Level_Up;

	private:
		Image* level_bar;
		Image* Charactor;
		Image* health;
		Image* health_zero;
		Image* Ex_value;
		Image* menuImg;


		Image* Skills[5]
			=
		{
			Wind,
			Blade,
			Power_up,
			Lightning
		};

		Image* Wind;
		Image* Blade;
		Image* Power_up;
		Image* Lightning;

		eItems selected_item;

		int Num1;
		int Num2;
		int Num3;
	};
}

