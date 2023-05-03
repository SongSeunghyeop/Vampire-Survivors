#pragma once
#include "myResourceManager.h"
#include "myGameObject.h"
#include "myImage.h" 
#include "PlaySceneManager.h"

namespace my
{
	class Treasure;
	class Magnet;

	class ItemManager : public GameObject
	{
	public:
		enum class eItems
		{
			LIGHTNING,
			AX1,
			BOOK,
			CROSS,
			WIND,
			POWER_UP,
			ARMOR,
			EMEPY_BOOK,
			HEART,
			NONE,
		};

		struct Item_Info
		{
			Image *item_image;
			Image *item_image2;
			Image* item_icon;
			Image* item_icon2;
			int item_level = 0;
			bool inited = false;
			std::wstring item_name;
			std::wstring item_name2;
			std::wstring item_effect;
			std::wstring item_effect2;
		};
	
		ItemManager();
		~ItemManager();

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
		void ax1();

	private:
		Animator* Treasure_show;

		Transform* Tr;

		eItems selected_item;

		int Num1;
		int Num2;
		int Num3;

		int Item_Num;

		Item_Info *items;
		std::vector<Item_Info*>::iterator it;
		HFONT font1;
		HFONT font2;
		HFONT oldfont;

		std::wstring new_item;
		std::wstring name1;
		std::wstring name2;
		std::wstring name3;
		std::wstring num1_LV;
		std::wstring num2_LV;
		std::wstring num3_LV;
		std::wstring info1;
		std::wstring info2;
		std::wstring info3;

		Image* menuImg;
		Image* Tresure_UI;

		Treasure * treasure;
		Magnet* magnet;

		std::vector<Image*> item_order;
		std::vector<Image*> item_order2;

		Image* Item_list;
	};
}