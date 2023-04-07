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
			POWER_UP,
			LIGHTNING,
			BOOK,
			ARMOR,
			EMEPY_BOOK,
			NONE,
		};

		LevelManager();
		~LevelManager();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void speed_up();
		void light_up();
		void power_up();
		void book_up();
		void armor_up();
		void empty_book();

		static bool Level_Up;
		static bool Show_on;

	private:
		Animator* Treasure_show;

		Transform* Tr;
		Image* level_bar;
		Image* Charactor;
		Image* health;
		Image* health_zero;
		Image* Ex_value;
		Image* menuImg;
		Image* Item_list;
		Image* Tresure_UI;

		Image* Skills[6]
			=
		{
			Wind,
			Power_up,
			Lightning,
			Book,
			Armor,
			Empty_Book,
		};

		Image* Wind;
		Image* Power_up;
		Image* Lightning;
		Image* Book;
		Image* Armor;
		Image* Empty_Book;

		eItems selected_item;

		int Num1;
		int Num2;
		int Num3;
	};
}

