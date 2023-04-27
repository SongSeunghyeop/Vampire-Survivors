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
#include "Sound.h"
#include "Effect2.h"

namespace my
{
	//Skills
	class Radar;
	class Warning_animation;
	class Krochi_after;
	class SkillManager;

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

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void onCollisionStay(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionEnter(class Collider* other) override;

		static Vector2 getPlayerPos() { return Krochi::Playerpos; }
		
		static float getPlayerPower(std::wstring p) 
		{ 
			if(p == L"Lightning")
				return Krochi::Light_Power + spinach;
			if (p == L"Book")
				return Krochi::Books_Power + spinach;
			if(p == L"Cross")
				return Krochi::Cross_Power + spinach;
			if (p == L"Ax1")
				return Krochi::Ax_Power + spinach;
		}
		static ePlayerState getPlayerState() { return mState; }
		
	public:
		static int Death_count;
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
		static int Cross_Power;
		static int Light_Power;
		static int Books_Power;
		static int Ax_Power;
		static float Cross_Time;
		static float Light_Time;
		static float Books_Time;
		static float Ax_Time;
		static int bookNum;
		static int LightNum;
		static int CrossNum;
		static int axNum;
		static float Armor;
		static float recovery;
		static float defaultTime;
		static float spinach; // ½Ã±ÝÄ¡
		Animator* playerAnimator;

		Image* playerImg_R;
		Image* playerImg_L;
		Image* damaged_R;
		Image* damaged_L;
		Image* die_R;
		Image* die_L;

		//Skills
		SkillManager* skillmanager;
		Radar* radar;
		//
		Krochi_after	*after;
		Warning_animation* wa;
		// --- move
		void move();
		void idle();
		void Damaged(ePlayerState mState);
		void level_up(); 
		void show_on();
		void death();

		// --- Skill
		void cross_();
		void Light();
		void Books();
		void ax1();
		void ax2();
		void magnet();

		int Magnet_power;
		float Magnet_Time;

		Sound* Light_sound;
		Sound* cross_sound;
		Sound* Gem;
		Sound* lvup;
		Sound* hpup;
		Sound* ax_sound;
		Sound* ax2_sound;
		Sound* magnet_sound;
		Sound* flame_sound;

		bool upGrade;
		friend class PlaySceneManager;
		friend class ItemManager;
	};
}

