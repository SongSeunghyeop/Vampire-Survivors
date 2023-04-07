#pragma once
#include "myResourceManager.h"
#include "MyGameObject.h"
#include "MyApplication.h"
#include "myTransform.h"
#include "myCollider.h"
#include "myAnimator.h"
#include "Time.h"
#include "myObject.h"
#include "myImage.h"
#include "myInput.h"


namespace my
{
	//Skills
	class Blade_L;
	class Blade_R;
	class Lightning;
	class Radar;
	class Ax;
	class Book;

	class Krochi_after;
	class Krochi : public GameObject
	{
	public:
		enum class ePlayerState
		{
			Move,
			Death,
			Idle,
			LevelUP,
			ShowOn,
		};
		enum class eSkillState
		{
			Skill_On,
			Skill_Off,
		};

		Krochi();
		~Krochi();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void onCollisionStay(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionEnter(class Collider* other) override;

		//static Vector2 getPlayerPos() { return Krochi::Playerpos; }
		static Vector2 getPlayerPos() { return Krochi::Playerpos; }
		
		static float getPlayerPower(std::wstring p) 
		{ 
			if(p == L"Lightning")
				return Krochi::Light_Power;
			if (p == L"Book")
				return Krochi::Books_Power;
			if(p == L"Blade")
				return Krochi::Blade_Power;
		}
		static ePlayerState getPlayerState() { return mState; }
	
	protected:
		static ePlayerState mState;
		static eSkillState skillState;

		static bool Right_Dir;
		static bool P_Damaged;
		static Vector2 Playerpos;

	private:

		static float Hp;
		static float Exp;
		static float Monster_Exp;
		static int level;
		static float vel;
		static float Power_up;
		static int Blade_Power;
		static int Light_Power;
		static int Books_Power;
		static float Blade_Time;
		static float Light_Time;
		static float Books_Time;
		static int bookNum;
		static int LightNum;
		static float Armor;
		static float defaultTime;

		Animator* playerAnimator;

		Image* playerImg_R;
		Image* playerImg_L;
		Image* damaged_R;
		Image* damaged_L;

		Blade_R *bladeR;
		Blade_L *bladeL;

		Ax* ax;
		Book* book1;

		Radar* radar;

		Krochi_after	*after;

		// --- move
		void move();
		void idle();
		void Damaged(ePlayerState mState);
		void level_up(); 
		void show_on();

		// --- Skill
		void Blade();
		void Light();
		void Books();

		int EnemyIndex[200] = { 0 };
		int EnemyNum;
		int randNum;

		friend class LevelManager;
	};
}

