#pragma once
#include "myResourceManager.h"
#include "myGameObject.h"
#include "myImage.h" 
#include "krochi.h"

namespace my
{
	class PlayerManager : public GameObject
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
			CROSS,
			HEART,
			NONE,
		};

		struct Item_Info
		{
			Image *item_image;
			int item_level = 1;
		};
	
		PlayerManager();
		~PlayerManager();

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
		void cross_up();
		void heart_up();

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

		eItems selected_item;

		int Num1;
		int Num2;
		int Num3;

		float Play_Time;

		Item_Info* Skills;

		HFONT font1;
		HFONT font2;

		HFONT oldfont;
	};
}

