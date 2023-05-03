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

	//캐릭터 정보
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

		Krochi::Hp = 112.0f;//112
		Krochi::Exp = 0.0f; // max = 1126.0f
		Krochi::level = 1;
		Krochi::Monster_Exp = 400; // 400
		Krochi::vel = 170.0f;
		Krochi::Cross_Time = 3.0f;
		Krochi::Light_Time = 3.0f;
		Krochi::Books_Time = 3.0f;
		Krochi::Ax_Time = 3.0f;
		Krochi::bookNum = 1;
		Krochi::LightNum = 1;
		Krochi::axNum = 1;
		Krochi::CrossNum = 1;
		Krochi::Cross_Power = 65;
		Krochi::Light_Power = 120;
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

		playerAnimator = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		playerAnimator->CreateAnimation(L"Idle_R", playerImg_R, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255); // 스프라이트 배열로 쪼개진 하나의 애니메이션 생성
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

		//화면의 중앙에 배치
		Krochi::Playerpos.x = myapplication.GetWidth() / 2;
		Krochi::Playerpos.y = myapplication.GetHeight() / 2;

		tr->setPos(Krochi::Playerpos);
		tr->setScale(Vector2(2.1f, 1.8f));

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(-13, -34));
		collider->setSize(Vector2(55, 61));

		//플레이어 주위의 레이더와 , 플레이어 그림자 생성
		radar = object::Instantiate<Radar>(Krochi::Playerpos, eLayerType::RADAR);
		after = object::Instantiate<Krochi_after>(Krochi::Playerpos, eLayerType::PLAYERAFTER);
		skillmanager = object::Instantiate<SkillManager>(eLayerType::PLAYER);
		//그림자와 플레이어 사이의 거리 조절
		after->SetShadow(6);

		//무브 스테이트, 스킬스테이트 분류
		mState = ePlayerState::Idle;
		skillState = eSkillState::Skill_On;

		Right_Dir = true;

		Light_sound
			= ResourceManager::Load<Sound>(L"Lightning_Sound", L"..\\Resources\\Sound\\sfx_lightningimpact.wav");
		ax_sound
			= ResourceManager::Load<Sound>(L"ax_sound", L"..\\Resources\\Sound\\cross_01.wav");
		ax2_sound
			= ResourceManager::Load<Sound>(L"ax2_sound", L"..\\Resources\\Sound\\wind_003.wav");
		Gem
			= ResourceManager::Load<Sound>(L"Gem", L"..\\Resources\\Sound\\sfx_gem.wav");
		lvup
			= ResourceManager::Load<Sound>(L"lvup", L"..\\Resources\\Sound\\sfx_levelup.wav");
		hpup
			= ResourceManager::Load<Sound>(L"hpup", L"..\\Resources\\Sound\\sfx_sounds_powerup2.wav");
		magnet_sound
			= ResourceManager::Load<Sound>(L"magnet_sound", L"..\\Resources\\Sound\\sfx_sounds_powerup18.wav");
		cross_sound
			= ResourceManager::Load<Sound>(L"cross_sound", L"..\\Resources\\Sound\\ax_02.wav");
		flame_sound
			= ResourceManager::Load<Sound>(L"flame_sound", L"..\\Resources\\Sound\\flame_sound.wav");
		GameObject::Initialize();
	}
	void Krochi::Update()
	{
		//레이더의 크기 화면 크기와 비슷하게 조절
		radar->radar_Collider->setSize(radar->Radar_Size);

		switch (mState)
		{
			//무브 스테이트
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
			//스킬 스테이트
			Light(); // 기본 스킬 

			if (Krochi::Books_Power >= 55)
				Books();
			if (Krochi::Cross_Power >= 70)
				cross_();
			if (Krochi::Ax_Power >= 90)
			{
				if (!upGrade)
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


			if (PlaySceneManager::Play_Time > EnemyManager::boss_Time + 5.7f)
			{
				if (wa == NULL)
					wa = object::Instantiate<Warning_animation>(Krochi::Playerpos + Vector2(3, -110), eLayerType::EFFECT);
			}
			if (PlaySceneManager::Play_Time > EnemyManager::boss_Time - 6.5f
				&& PlaySceneManager::Play_Time < EnemyManager::boss_Time + 6.0f)
			{
				Krochi::Hp = 112.0f;

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
		//Hp 가 0 이면 캐릭터 사망
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

		//피해를 입었을 때에도, 움직이거나 멈춰있는 상태는 유지해야하기 때문에
		//스테이트를 바꾸지 않고 그 스테이트에서 애니메니션만 변경
		if (Krochi::P_Damaged)
			Damaged(ePlayerState::Idle);

		//방향키 입력시 스테이트 전환, 방향 미리 선정
		for (int i = 0; i < 4; i++)
		{
			if (Input::GetKeyDown(eKeyCode(i)) || Input::GetKey(eKeyCode(i)))
			{
				mState = ePlayerState::Move;

				if (eKeyCode(i) == eKeyCode::A)
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

		//두 방향에 따른 애니메이션
		if (Right_Dir)
			playerAnimator->Play_NO_RE(L"RightRun", true);

		if (!Right_Dir)
			playerAnimator->Play_NO_RE(L"LeftRun", true);

		if (Krochi::P_Damaged)
			Damaged(ePlayerState::Move);

		//키 입력을 멈추었을 때 그 방향을 유지하면서 스테이트 변경
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

		//반대되는 방향의 키를 동시에 입력하면, 움직임을 멈추도록 설정
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
		//플레이어의 HP 감소
		if (Hp > 10)
			Hp -= Time::getDeltaTime() * (6.0f - Armor);
	
		//데미지를 입는 상황에서 스테이트가 변하면 , 애니메이션을 바꿔주어야함
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
		//레벨업을 하면, 레이더의 크기를 0으로 줄임
		//몬스터는 레이더에 감지되지 않으면 이동을멈춤
		radar->radar_Collider->setSize(Vector2::Zero);

		PlaySceneManager::Level_Up = true;
	}
	void Krochi::show_on()
	{
		//보물 상자를 열었을 때도 레벨업 했을 때와 같은 기능 적용
		radar->radar_Collider->setSize(Vector2::Zero);
		Ax_Time = 0.0f;
		PlaySceneManager::Show_on = true;
	}
	void Krochi::magnet()
	{
		Magnet_Time += Time::getDeltaTime();
		Level_Item::Item_vel = 500.0f;

		if (Magnet_Time > 8.0f)
		{
			//magnet_sound->Play(false);
			Level_Item::Item_vel = 0.0f;
			Magnet_power = 0;
		}
	}
	//Skills
	void Krochi::ax1()
	{
		if (Krochi::Ax_Time > 4.9f - defaultTime)
		{
			ax_sound->Play(false);

			for (int i = 0; i < 8; i++)
			{
				if (Krochi::Ax_Power >= 85 + i * 5)
					axNum = i + 1;
			}

			skillmanager->skill_Instantiate(eSkillname::AX1, axNum);
			Krochi::Ax_Time = 0.0f + float(axNum) * 0.2f;
		}
	}
	void Krochi::ax2()
	{
		axNum = 18;

		if (Krochi::Ax_Time > 4.0f - defaultTime)
		{
			ax2_sound->Play(false);
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

		if (Krochi::Books_Time > 6.4f - defaultTime)
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

		if (Krochi::Cross_Time > 3.4f - defaultTime)
		{
			cross_sound->Play(false);
			skillmanager->skill_Instantiate(eSkillname::CROSS, CrossNum);

			Krochi::Cross_Time = 0.0f + float(CrossNum) * 0.1f;
		}
	}
	void Krochi::Light()
	{
		for (int i = 0; i < 8; i++)
		{
			if (Krochi::Light_Power >= 120 + i * 5)
				LightNum = i + 1;
		}

		if (Krochi::Light_Time > 5.4f - defaultTime) // 5.5
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

			Light_sound->Play(false);
			Krochi::Light_Time = 0.0f + float(LightNum) * 0.2f;
		}
	}

	void Krochi::onCollisionEnter(Collider* other)
	{
		//경험치 아이템
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
				spinach += 0.2f;
				Armor += 0.2f;
				mState = ePlayerState::LevelUP;
			}
		}
		//회복 아이템
		if (other->getOwner()->getName() == L"Chicken")
		{
			hpup->Play(false);

			Hp += 50.0f;

			if (Hp > 113)
				Hp = 113;
		}
		//보스 몬스터의 공격 스킬
		if (other->getOwner()->getName() == L"meteor")
		{
			Krochi::Hp -= 12.0f;
			flame_sound->Play(false);
			Effect2* mEffect = object::Instantiate<Effect2>
				(Krochi::getPlayerPos() + Vector2(-20.0f, -20.0f), eLayerType::EFFECT);
		}
		if (other->getOwner()->getName() == L"dBullet")
		{
			Krochi::Hp -= 0.1f;
			object::Destory(other->getOwner());
		}
		//몬스터
		if (other->getOwner()->getName() == L"Enemy"
			|| other->getOwner()->getName() == L"dBullet")
		{
			Krochi::P_Damaged = true;
		}
		//보물상자
		if (other->getOwner()->getName() == L"Treasure")
		{
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
			if (other->getOwner()->getState() == GameObject::eState::Death)
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