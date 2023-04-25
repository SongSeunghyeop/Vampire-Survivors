#include "EnemyManager.h"
#include "PlaySceneManager.h"
#include "Krochi.h"
#include "Radar.h"
#include "Krochi_after.h"
#include "Level_Item.h"
#include "Boss.h"
#include "warning_animation.h"
//
#include "SkillManager.h"

#pragma comment(lib, "msimg32.lib")

extern my::Application myapplication;

namespace my
{
	Vector2 Krochi::Playerpos = Vector2(100.f, 100.f);

	//Ä³¸¯ÅÍ Á¤º¸
	bool Krochi::P_Damaged;
	float Krochi::Hp;
	float Krochi::Exp;
	float Krochi::Monster_Exp;
	float Krochi::vel;
	float Krochi::Cross_Time;
	float Krochi::Light_Time;
	float Krochi::Books_Time;
	int		Krochi::Ax_Power;
	float Krochi::Ax_Time;
	float Krochi::Power_up;
	int    Krochi::level;
	int    Krochi::Cross_Power;
	int    Krochi::Light_Power;
	int    Krochi::Books_Power;
	int		Krochi::bookNum;
	int		Krochi::LightNum;
	int	    Krochi::axNum;
	int		Krochi::CrossNum;
	float Krochi::Armor;
	float Krochi::defaultTime;
	float Krochi::recovery;
	int    Krochi::Death_count;
	float Krochi::spinach;

	Krochi::Krochi()
	{
		this->setName(L"Player");

		Krochi::Hp = 112.0f;
		Krochi::Exp = 0.0f; // max = 1126.0f
		Krochi::level = 1;
		Krochi::Monster_Exp = 400; // 400
		Krochi::vel = 160.0f;
		Krochi::Cross_Time = 3.0f;
		Krochi::Light_Time = 3.0f;
		Krochi::Books_Time = 3.0f;
		Krochi::Ax_Time = 3.0f;
		Krochi::bookNum = 1;
		Krochi::LightNum = 1; 
		Krochi::axNum = 1; 
		Krochi::CrossNum = 1;
		Krochi::Cross_Power = 65;
		Krochi::Light_Power = 100;
		Krochi::Books_Power = 50;
		Krochi::Ax_Power = 85;
		Krochi::Armor = 0;
		Krochi::Power_up = 0;
		Krochi::defaultTime = 0;
		Krochi::recovery = 0.0f;
		Krochi::Death_count = 0;
		Krochi::spinach = 0;
	}
	void Krochi::Initialize()
	{
		playerImg_R = ResourceManager::Load<Image>(L"PlayerR1", L"..\\Resources\\Arca_RightRun.bmp");
		playerImg_L = ResourceManager::Load<Image>(L"PlayerL1", L"..\\Resources\\Arca_LeftRun.bmp");
		damaged_R = ResourceManager::Load<Image>(L"damaged_R", L"..\\Resources\\Arca_CollRight.bmp");
		damaged_L = ResourceManager::Load<Image>(L"damaged_L", L"..\\Resources\\Arca_CollLeft.bmp");
		die_R = ResourceManager::Load<Image>(L"Die_Right", L"..\\Resources\\Die_Right.bmp");
		die_L = ResourceManager::Load<Image>(L"Die_Left", L"..\\Resources\\Die_Left.bmp");

 		playerAnimator = AddComponent<Animator>(); // ¾Ö´Ï¸ÞÀÌÅÍ ÄÄÆ÷³ÍÆ® ¹è¿­¿¡ µ¿ÀûÇÒ´ç ¹× ÃÊ±âÈ­
		playerAnimator->CreateAnimation(L"Idle_R", playerImg_R, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255); // ½ºÇÁ¶óÀÌÆ® ¹è¿­·Î ÂÉ°³Áø ÇÏ³ªÀÇ ¾Ö´Ï¸ÞÀÌ¼Ç »ý¼º
  	 	playerAnimator->CreateAnimation(L"Idle_L", playerImg_L, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"RightRun", playerImg_R, Vector2::Zero, 3, 1, 3, 0.25f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"LeftRun", playerImg_L, Vector2::Zero, 3, 1, 3, 0.25f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_IdleR", damaged_R, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_IdleL", damaged_L, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_RunR", damaged_R, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_RunL", damaged_L, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Die_Right", die_R, Vector2::Zero, 3, 1, 3, 0.15f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Die_Left", die_L, Vector2::Zero, 3, 1, 3, 0.15f, 255, 0, 255);

		playerAnimator->Play(L"Idle_R", true);

		Transform* tr = GetComponent<Transform>();

		//È­¸éÀÇ Áß¾Ó¿¡ ¹èÄ¡
 		Krochi::Playerpos.x = myapplication.GetWidth() / 2 ;
 		Krochi::Playerpos.y = myapplication.GetHeight() / 2 ;

		tr->setPos(Krochi::Playerpos);
		tr->setScale(Vector2(2.1f,1.8f));

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(-13, -34));
		collider->setSize(Vector2(55, 61));

		//ÇÃ·¹ÀÌ¾î ÁÖÀ§ÀÇ ·¹ÀÌ´õ¿Í , ÇÃ·¹ÀÌ¾î ±×¸²ÀÚ »ý¼º
		radar = object::Instantiate<Radar>(Krochi::Playerpos, eLayerType::RADAR);
		after = object::Instantiate<Krochi_after>(Krochi::Playerpos, eLayerType::PLAYERAFTER);
		skillmanager = object::Instantiate<SkillManager>(eLayerType::PLAYER);
		//±×¸²ÀÚ¿Í ÇÃ·¹ÀÌ¾î »çÀÌÀÇ °Å¸® Á¶Àý
		after->SetShadow(5);

		//¹«ºê ½ºÅ×ÀÌÆ®, ½ºÅ³½ºÅ×ÀÌÆ® ºÐ·ù
		mState = ePlayerState::Idle;
		skillState = eSkillState::Skill_On;

		Right_Dir = true;

		Light_sound
			= ResourceManager::Load<Sound>(L"Lightning_Sound", L"..\\Resources\\Sound\\sfx_lightningimpact.wav");
		Gem 
			= ResourceManager::Load<Sound>(L"Gem", L"..\\Resources\\Sound\\sfx_gem.wav");
		lvup
			=ResourceManager::Load<Sound>(L"lvup", L"..\\Resources\\Sound\\sfx_levelup.wav");
		hpup
			= ResourceManager::Load<Sound>(L"hpup", L"..\\Resources\\Sound\\sfx_sounds_powerup2.wav");

 		GameObject::Initialize();
	}
	void Krochi::Update()
	{
		//·¹ÀÌ´õÀÇ Å©±â È­¸é Å©±â¿Í ºñ½ÁÇÏ°Ô Á¶Àý
		radar->radar_Collider->setSize(radar->Radar_Size);

		switch (mState)
		{
			//¹«ºê ½ºÅ×ÀÌÆ®
		case my::Krochi::ePlayerState::Move:
			move();
			break;
		case my::Krochi::ePlayerState::Idle:
			idle();
			break;
		case  my::Krochi::ePlayerState::LevelUP:
			level_up();
			break;
		case  my::Krochi::ePlayerState::ShowOn:
		{
			show_on();

			upGrade = true;
		}
			break;
		case  my::Krochi::ePlayerState::Death:
			death();
			break;
		default:
			break;
		}
		switch (skillState)
		{
		case my::Krochi::eSkillState::Skill_On:
		{
			//½ºÅ³ ½ºÅ×ÀÌÆ®
			Light(); // ±âº» ½ºÅ³ 

			if(Krochi::Books_Power >= 55)
				Books();
			if (Krochi::Cross_Power >= 70)
				cross_();
			if (Krochi::Ax_Power >= 90)
			{
				if(!upGrade)
					ax1();
				if (upGrade)
					ax2();
			}
			if (Magnet_power == 1)
				magnet();

			Krochi::Cross_Time += Time::getDeltaTime();
			Krochi::Light_Time += Time::getDeltaTime();
			Krochi::Books_Time += Time::getDeltaTime();
			Krochi::Ax_Time += Time::getDeltaTime();
			Krochi::Hp += recovery * Time::getDeltaTime();

<<<<<<< HEAD

			if (PlaySceneManager::Play_Time > EnemyManager::boss_Time + 5.5f)
=======
			if (PlaySceneManager::Play_Time > EnemyManager::boss_Time - 2.0f 
				&& !EnemyManager::Boss_on) // º¸½º°¡ µîÀåÇÏ±â 1ÃÊ Àü, Light ÄðÅ¸ÀÓ ÃÊ±âÈ­
			{
				Krochi::Light_Power = 0.0f;
			}
			if (PlaySceneManager::Play_Time > EnemyManager::boss_Time + 1.0f)
>>>>>>> parent of 76d27cb (2023.04.17 ìµœì¢…ìˆ˜ì •)
			{
				if(wa == NULL)
					wa = object::Instantiate<Warning_animation>(Krochi::Playerpos + Vector2(3,-110), eLayerType::EFFECT);
			}
			if (PlaySceneManager::Play_Time > EnemyManager::boss_Time - 5.6f 
				&& PlaySceneManager::Play_Time <  EnemyManager::boss_Time + 5.5f)
			{
				Krochi::Hp = 100.0f;

				Light_Time = 0.0f;
				Books_Time = 0.0f;
				Ax_Time = 0.0f;
				Cross_Time = 0.0f;

				Right_Dir = true;
				mState = Krochi::ePlayerState::Idle;
			}
		}
			break;

		case my::Krochi::eSkillState::Skill_Off:
		{
			Level_Item::Item_vel = 0.0f;
		}
			break;
		default:
			break;
		}
		//Hp °¡ 0 ÀÌ¸é Ä³¸¯ÅÍ »ç¸Á
		if (Krochi::Hp < 0)
		{
			object::Destory(after);
			mState = ePlayerState::Death;
		}

		GameObject::Update();
	}

	void Krochi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Krochi::Release()
	{
		GameObject::Release();
	}

	void Krochi::death()
	{
		if (Right_Dir)
			playerAnimator->Play_NO_RE(L"Die_Right", false);
		if (!Right_Dir)
			playerAnimator->Play_NO_RE(L"Die_Left", false);
	}

	void Krochi::idle()
	{
		if (Right_Dir)
				playerAnimator->Play_NO_RE(L"Idle_R", true);
		if (!Right_Dir)
				playerAnimator->Play_NO_RE(L"Idle_L", true);

		//ÇÇÇØ¸¦ ÀÔ¾úÀ» ¶§¿¡µµ, ¿òÁ÷ÀÌ°Å³ª ¸ØÃçÀÖ´Â »óÅÂ´Â À¯ÁöÇØ¾ßÇÏ±â ¶§¹®¿¡
		//½ºÅ×ÀÌÆ®¸¦ ¹Ù²ÙÁö ¾Ê°í ±× ½ºÅ×ÀÌÆ®¿¡¼­ ¾Ö´Ï¸Þ´Ï¼Ç¸¸ º¯°æ
		if (Krochi::P_Damaged)
				Damaged(ePlayerState::Idle);

		//¹æÇâÅ° ÀÔ·Â½Ã ½ºÅ×ÀÌÆ® ÀüÈ¯, ¹æÇâ ¹Ì¸® ¼±Á¤
		for (int i = 0; i < 4; i++)
		{
			if (Input::GetKeyDown(eKeyCode(i)) || Input::GetKey(eKeyCode(i)))
			{
				mState = ePlayerState::Move;

				if(eKeyCode(i) == eKeyCode::A)
					Right_Dir = false;
				if (eKeyCode(i) == eKeyCode::D)
					Right_Dir = true;
			}
		}
	}

	void Krochi::move()
	{
		Transform* tr = GetComponent<Transform>();
		Playerpos = tr->getPos();

		//µÎ ¹æÇâ¿¡ µû¸¥ ¾Ö´Ï¸ÞÀÌ¼Ç
		if (Right_Dir)
			playerAnimator->Play_NO_RE(L"RightRun", true);

		if (!Right_Dir)
			playerAnimator->Play_NO_RE(L"LeftRun", true);

		if (Krochi::P_Damaged)
			Damaged(ePlayerState::Move);

		//Å° ÀÔ·ÂÀ» ¸ØÃß¾úÀ» ¶§ ±× ¹æÇâÀ» À¯ÁöÇÏ¸é¼­ ½ºÅ×ÀÌÆ® º¯°æ
		for (int i = 0; i < 4; i++)
		{
			if (Input::GetKeyUp(eKeyCode(i)))
			{
				mState = ePlayerState::Idle;

				if (eKeyCode(i) == eKeyCode::A)
					Right_Dir = false;
				if (eKeyCode(i) == eKeyCode::D)
					Right_Dir = true;
			}
		}

		//¹Ý´ëµÇ´Â ¹æÇâÀÇ Å°¸¦ µ¿½Ã¿¡ ÀÔ·ÂÇÏ¸é, ¿òÁ÷ÀÓÀ» ¸ØÃßµµ·Ï ¼³Á¤
		if (Input::GetKey(eKeyCode::A) && Input::GetKey(eKeyCode::D))
		{
			mState = ePlayerState::Idle;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			Right_Dir = false;
			Playerpos.x -= vel * Time::getDeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Right_Dir = true;
			Playerpos.x += vel * Time::getDeltaTime();
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Playerpos.y -= vel * Time::getDeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			Playerpos.y += vel * Time::getDeltaTime();
		}

		tr->setPos(Playerpos);
	}

	void Krochi::Damaged(ePlayerState state)
	{
		//ÇÃ·¹ÀÌ¾îÀÇ HP °¨¼Ò
		if(Hp > 10)
			Hp -= Time::getDeltaTime() * (5.5f - Armor);	
		if (EnemyManager::Boss_on)
			Hp -= Time::getDeltaTime() * (2.5f - Armor);
		//µ¥¹ÌÁö¸¦ ÀÔ´Â »óÈ²¿¡¼­ ½ºÅ×ÀÌÆ®°¡ º¯ÇÏ¸é , ¾Ö´Ï¸ÞÀÌ¼ÇÀ» ¹Ù²ãÁÖ¾î¾ßÇÔ
		if (state == ePlayerState::Idle)
		{
			if (Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_IdleR", true);

			if (!Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_IdleL", true);
		}
		if (state == ePlayerState::Move)
		{
			if (Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_RunR", true);

			if (!Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_RunL", true);
		}
	}

	void Krochi::level_up()
	{
		//·¹º§¾÷À» ÇÏ¸é, ·¹ÀÌ´õÀÇ Å©±â¸¦ 0À¸·Î ÁÙÀÓ
		//¸ó½ºÅÍ´Â ·¹ÀÌ´õ¿¡ °¨ÁöµÇÁö ¾ÊÀ¸¸é ÀÌµ¿À»¸ØÃã
		radar->radar_Collider->setSize(Vector2::Zero);
		
		PlaySceneManager::Level_Up = true;
	}
	void Krochi::show_on()
	{
		//º¸¹° »óÀÚ¸¦ ¿­¾úÀ» ¶§µµ ·¹º§¾÷ ÇßÀ» ¶§¿Í °°Àº ±â´É Àû¿ë
		radar->radar_Collider->setSize(Vector2::Zero);
		Ax_Time = 0.0f;
		PlaySceneManager::Show_on = true;
	}
	void Krochi::magnet()
	{
		Magnet_Time += Time::getDeltaTime();
		Level_Item::Item_vel = 500.0f;

		if (Magnet_Time > 5.0f)
		{
			Level_Item::Item_vel = 0.0f;
			Magnet_power = 0;
		}
	}
	//Skills
	void Krochi::ax1()
	{
		if(Krochi::Ax_Time > 5.0f - defaultTime)
		{
			for (int i = 0; i < 8; i++)
			{
				if (Krochi::Ax_Power >= 85 + i  * 5 )
					axNum = i + 1;
			}

			skillmanager->skill_Instantiate(eSkillname::AX1, axNum);
			Krochi::Ax_Time = 0.0f + float(axNum) * 0.2f;
		}
	}
	void Krochi::ax2()
	{
		axNum = 18;

		if (Krochi::Ax_Time > 3.5f - defaultTime)
		{
			skillmanager->skill_Instantiate(eSkillname::AX2, axNum);
			Krochi::Ax_Time = 0.0f;	
		}
	}
	void Krochi::Books()
	{
		for (int i = 0; i < 8; i++)
		{
			if (Krochi::Books_Power >= 50 + i * 5)
				bookNum = i + 1;
		}

		if (Krochi::Books_Time > 6.5f - defaultTime)
		{
			skillmanager->skill_Instantiate(eSkillname::BOOK, bookNum);
			Krochi::Books_Time = 0.0f;
		}
	}

	void Krochi::cross_()
	{
		for (int i = 0; i < 8; i++)
		{
			if (Krochi::Cross_Power >= 65 + i * 5)
				CrossNum = i + 1;
		}

		if (Krochi::Cross_Time > 3.5f - defaultTime)
		{
			skillmanager->skill_Instantiate(eSkillname::CROSS, CrossNum);

			Krochi::Cross_Time = 0.0f + float(CrossNum) * 0.1f;
		}
	}
	void Krochi::Light()
	{
		for (int i = 0; i < 8; i++)
		{
			if (Krochi::Light_Power >= 100 + i * 5)
				LightNum = i + 1;
		}

		if (Krochi::Light_Time > 5.5f - defaultTime) // 5.5
		{
			if (EnemyManager::Boss_on)
			{
				Lightning* light
					= object::Instantiate<Lightning>
					(Boss::getBossPos() + Vector2(12.0f, -174.0f), eLayerType::SKILL);
			}
			else
			{
				skillmanager->skill_Instantiate(eSkillname::LIGHT, LightNum);
			}

			Krochi::Light_Time = 0.0f + float(LightNum) * 0.2f;
		}

		Light_sound->Play(false);
	}

	void Krochi::onCollisionEnter(Collider* other)
	{
		//°æÇèÄ¡ ¾ÆÀÌÅÛ
		if (other->getOwner()->getName() == L"Level_Item"
			&& mState != ePlayerState::LevelUP)
		{
			Exp += Monster_Exp;
			Gem->Play(false);
			if (Exp > 1126.0f)
			{
				lvup->Play(false);
				Exp = 0.0f;
				Monster_Exp /= 1.15f;
				++Krochi::level;
				mState = ePlayerState::LevelUP;
			}
		}
		//È¸º¹ ¾ÆÀÌÅÛ
		if (other->getOwner()->getName() == L"Chicken")
		{
			hpup->Play(false);

			Hp += 50.0f;

			if (Hp > 113)
				Hp = 113;
		}
		//º¸½º ¸ó½ºÅÍÀÇ °ø°Ý ½ºÅ³
		if (other->getOwner()->getName() == L"meteor")
		{ 
			Krochi::Hp -= 15.0f;

			Effect2*mEffect = object::Instantiate<Effect2>
				(Krochi::getPlayerPos() + Vector2(-20.0f, -20.0f), eLayerType::EFFECT);
		}
		if (other->getOwner()->getName() == L"dBullet")
		{
			object::Destory(other->getOwner());
		}
		//¸ó½ºÅÍ
		if (other->getOwner()->getName() == L"Enemy"
			|| other->getOwner()->getName() == L"dBullet")
		{
			Krochi::P_Damaged = true;
		}
		//º¸¹°»óÀÚ
		if (other->getOwner()->getName() == L"Treasure")
		{
			ResourceManager::Find<Sound>(L"treasure_sound")->Play(false);
			mState = ePlayerState::ShowOn;
		}
		if (other->getOwner()->getName() == L"Magnet")
		{
			Magnet_power = 1;
		}
	}											
	void Krochi::onCollisionStay(Collider* other)
	{
		if (other->getOwner()->getName() == L"Enemy"
			|| other->getOwner()->getName() == L"dBullet")
		{
			if(other->getOwner()->getState() == GameObject::eState::Death)
			{
				Krochi::P_Damaged = false;
			}
		}
	}
	void Krochi::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Enemy"
			|| other->getOwner()->getName() == L"dBullet")
		{
			Krochi::P_Damaged = false;
		}
	}
}