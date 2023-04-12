#include "Krochi.h"

#include "Radar.h"
#include "Krochi_after.h"
#include "Lightning.h"
#include "Cross.h"
#include "Book.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

#pragma comment(lib, "msimg32.lib")

extern my::Application myapplication;

namespace my
{
	Vector2 Krochi::Playerpos = Vector2(100.f, 100.f);

	bool Krochi::P_Damaged;
	float Krochi::Hp;
	float Krochi::Exp;
	float Krochi::Monster_Exp;
	float Krochi::vel;
	float Krochi::Cross_Time;
	float Krochi::Light_Time;
	float Krochi::Books_Time;
	float Krochi::Power_up;
	int    Krochi::level;
	int    Krochi::Cross_Power;
	int    Krochi::Light_Power;
	int    Krochi::Books_Power;
	int		Krochi::bookNum;
	int		Krochi::LightNum;
	int		Krochi::CrossNum;
	float Krochi::Armor;
	float Krochi::defaultTime;
	float Krochi::recovery;

	Krochi::Krochi()
	{
		this->setName(L"Player");

		Krochi::Hp = 112.0f;
		Krochi::Exp = 0.0f; // max = 1126.0f
		Krochi::level = 1;
		Krochi::Monster_Exp = 350;
		Krochi::vel = 150.0f;
		Krochi::Cross_Time = 3.0f;
		Krochi::Light_Time = 3.0f;
		Krochi::Books_Time = 3.0f;
		Krochi::bookNum = 1;
		Krochi::LightNum = 1;
		Krochi::CrossNum = 1;
		Krochi::Cross_Power = 60;
		Krochi::Light_Power = 90;
		Krochi::Books_Power = 50;
		Krochi::Armor = 0;
		Krochi::Power_up = 0;
		Krochi::defaultTime = 0;
		Krochi::recovery = 0.0f;
	}
	Krochi::~Krochi()
	{

	}
	void Krochi::Initialize()
	{
		playerImg_R = ResourceManager::Load<Image>(L"PlayerR1", L"..\\Resources\\Player_RightRun.bmp");
		playerImg_L = ResourceManager::Load<Image>(L"PlayerL1", L"..\\Resources\\Player_LeftRun.bmp");
		damaged_R = ResourceManager::Load<Image>(L"damaged_R", L"..\\Resources\\Collision_RightRun.bmp");
		damaged_L = ResourceManager::Load<Image>(L"damaged_L", L"..\\Resources\\Collision_LeftRun.bmp");
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
 		Krochi::Playerpos.x = myapplication.GetWidth() / 2 ;
 		Krochi::Playerpos.y = myapplication.GetHeight() / 2 ;
		tr->setPos(Krochi::Playerpos);
		tr->setScale(Vector2(2.1f,1.8f));

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(-13, -34));
		collider->setSize(Vector2(55, 61));

		radar = object::Instantiate<Radar>(Krochi::Playerpos, eLayerType::RADAR);
		after = object::Instantiate<Krochi_after>(Krochi::Playerpos, eLayerType::PLAYERAFTER);

		after->SetShadow(5);

		mState = ePlayerState::Idle;
		skillState = eSkillState::Skill_On;

		Right_Dir = true;

 		GameObject::Initialize();
	}
	void Krochi::Update()
	{
		radar->radar_Collider->setSize(radar->Radar_Size);

		switch (mState)
		{
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
			show_on();
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
			Light();
			if(Krochi::Books_Power >= 53)
				Books();
			if (Krochi::Cross_Power >= 65)
				cross_();

			Krochi::Cross_Time += Time::getDeltaTime();
			Krochi::Light_Time += Time::getDeltaTime();
			Krochi::Books_Time += Time::getDeltaTime();
			Krochi::Hp += recovery * Time::getDeltaTime();
		}
			break;
		case my::Krochi::eSkillState::Skill_Off:
			break;
		default:
			break;
		}

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

		if (Krochi::P_Damaged)
				Damaged(ePlayerState::Idle);

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

		if (Right_Dir)
			playerAnimator->Play_NO_RE(L"RightRun", true);

		if (!Right_Dir)
			playerAnimator->Play_NO_RE(L"LeftRun", true);

		if (Krochi::P_Damaged)
			Damaged(ePlayerState::Move);

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
		Hp -= Time::getDeltaTime() * (5.5f - Armor);	

		if(EnemyManager::Boss_on)
			Hp -= Time::getDeltaTime() * 2.5f;

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
		radar->radar_Collider->setSize(Vector2::Zero);
		PlayerManager::Level_Up = true;
	}
	void Krochi::show_on()
	{
		radar->radar_Collider->setSize(Vector2::Zero);
		PlayerManager::Show_on = true;
	}

	void Krochi::Books()
	{
		if (Krochi::Books_Time > 6.5f - defaultTime)
		{
			if (Krochi::Books_Power >= 53)
				bookNum = 2;
			if (Krochi::Books_Power >= 56)
				bookNum = 3;
			if (Krochi::Books_Power >= 59)
				bookNum = 4;
			if (Krochi::Books_Power >= 62)
				bookNum = 5;
			if (Krochi::Books_Power >= 65)
				bookNum = 6;
			if (Krochi::Books_Power >= 68)
				bookNum = 7;
			if (Krochi::Books_Power >= 71)
				bookNum = 8;

			for (int i = 0; i < bookNum; i++)
			{
				book1 = object::Instantiate<Book>(Krochi::Playerpos, eLayerType::SKILL);
				book1->setR(360 / bookNum * (i));
				book1->setDistance(75 + (bookNum * 15));
				book1->setVel(120 + (bookNum * 10));
				book1->setTime(2.0f + (bookNum * 0.3f));
			}
			Krochi::Books_Time = 0.0f;
		}
	}

	void Krochi::cross_()
	{
		if (Krochi::Cross_Time > 5.8f - defaultTime)
		{
			if (Krochi::Cross_Power >= 65)
				CrossNum = 2;
			if (Krochi::Cross_Power >= 70)
				CrossNum = 3;
			if (Krochi::Cross_Power >= 75)
				CrossNum = 4;
			if (Krochi::Cross_Power >= 80)
				CrossNum = 5;
			if (Krochi::Cross_Power >= 85)
				CrossNum = 6;
			if (Krochi::Cross_Power >= 90)
				CrossNum = 7;
			if (Krochi::Cross_Power >= 95)
				CrossNum = 8;

			for (int i = 0; i < CrossNum; i++)
			{
				int r = rand() % 360 + 1;

				Cross *cross = new Cross();
				Scene* scene = SceneManager::getActiveScene();
				scene->AddGameObj(cross, eLayerType::SKILL);
				cross->GameObject::GetComponent<Transform>()->setPos(Krochi::Playerpos);
				cross->setCrossScale(2.8f + CrossNum * 0.2f);
				cross->setR(r);
				cross->Initialize();
			}

			//ax = object::Instantiate<Ax>(Krochi::Playerpos, eLayerType::SKILL);
			//ax->setR(135);
			//ax = object::Instantiate<Ax>(Krochi::Playerpos, eLayerType::SKILL);
			//ax->setR(180);
			//ax = object::Instantiate<Ax>(Krochi::Playerpos, eLayerType::SKILL);
			//ax->setR(225);
			//ax = object::Instantiate<Ax>(Krochi::Playerpos, eLayerType::SKILL);
			//ax->setR(270);
			//ax = object::Instantiate<Ax>(Krochi::Playerpos, eLayerType::SKILL);
			//ax->setR(315);

			Krochi::Cross_Time = 0.0f + float(CrossNum) * 0.2f;
		}
	}
	void Krochi::Light()
	{
		if (Krochi::Light_Power >= 95)
			LightNum = 2;
		if (Krochi::Light_Power >= 100)
			LightNum = 3;
		if (Krochi::Light_Power >= 105)
			LightNum = 4;
		if (Krochi::Light_Power >= 110)
			LightNum = 5;
		if (Krochi::Light_Power >= 115)
			LightNum = 6;
		if (Krochi::Light_Power >= 120)
			LightNum = 7;
		if (Krochi::Light_Power >= 125)
			LightNum = 8;

		if (Krochi::Light_Time > 6.0f - defaultTime)
		{ // 해시 테이블 활용
			randNum = 0;
			
			EnemyNum = Radar::getEnemies().size();

			if (EnemyNum < LightNum)
			{
				LightNum = EnemyNum;
			}

			for (int i = 0; i < LightNum; i++)
			{
				while(EnemyIndex[randNum] == 1)
					randNum = rand() % EnemyNum;

				EnemyIndex[randNum] = 1;
				Vector2 target = Radar::getEnemies()[randNum]->getPos();

				Lightning* light
					= object::Instantiate<Lightning>(target + Vector2(12.0f, -174.0f), eLayerType::SKILL);
			}
			for (int i = 0; i < EnemyNum; i++)
			{
				if (EnemyIndex[i] > 0)
					EnemyIndex[i] = 0;
			}

			Krochi::Light_Time = 0.0f + float(LightNum) * 0.3f;
		}
	}

	void Krochi::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Level_Item")
		{
			Exp += Monster_Exp;

			if (Exp > 1126.0f)
			{
				Exp = 0.0f;
				Monster_Exp /= 1.15f;
				++Krochi::level;
				mState = ePlayerState::LevelUP;
			}
		}
		if (other->getOwner()->getName() == L"Chicken")
		{
			Hp += 25.0f;

			if (Hp > 113)
				Hp = 113;
		}
		if (other->getOwner()->getName() == L"meteor")
		{ 
			Krochi::Hp -= 30.0f;

			Effect2*mEffect = object::Instantiate<Effect2>
				(Krochi::getPlayerPos() + Vector2(-20.0f, -20.0f), eLayerType::EFFECT);
		}
		if(other->getOwner()->getName() == L"Enemy")
			Krochi::P_Damaged = true;
		if (other->getOwner()->getName() == L"Treasure")
		{
			mState = ePlayerState::ShowOn;
		}
	}											
	void Krochi::onCollisionStay(Collider* other)
	{
	}
	void Krochi::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Enemy")
			Krochi::P_Damaged = false;
	}
}