#include "myResourceManager.h"
#include "White_Fly.h"
#include "Time.h"
#include "Effect.h"
#include "myObject.h"
#include "Level_Item.h"

namespace my
{
	White_Fly::White_Fly()
	{
		Entity::setName(L"Enemy");
		monster_hp = 100;
	}
	White_Fly::~White_Fly()
	{

	}

	void White_Fly::Initialize()
	{
		EnemyR_Img = ResourceManager::Load<Image>(L"EnemyR", L"..\\Resources\\Fly_R_All.bmp");
		EnemyL_Img = ResourceManager::Load<Image>(L"EnemyL", L"..\\Resources\\Fly_L_All.bmp");
		Damaged_R = ResourceManager::Load<Image>(L"Damaged_R", L"..\\Resources\\Damaged_R.bmp");
		Damaged_L = ResourceManager::Load<Image>(L"Damaged_L", L"..\\Resources\\Damaged_L.bmp");

		EnemyAnimator = AddComponent<Animator>();
		EnemyAnimator->CreateAnimation(L"RightWalk", EnemyR_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"LeftWalk", EnemyL_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Idle_R", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Idle_L", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Damaged_R", Damaged_R, Vector2::Zero, 2, 1, 2, 0.2f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Damaged_L", Damaged_L, Vector2::Zero, 2, 1, 2, 0.2f, 255, 0, 255);

		EnemyPos = GetComponent<Transform>();

		RandPos.x = rand() % 1400 - 700;  // -700 ~ 700
		RandPos.y = rand() % 800 - 400; //  -400 ~ 400

		while (RandPos.x > -560 && RandPos.x < 560) { // 1260
			RandPos.x = rand() % 1400 - 700;
		}
		while (RandPos.y > -280 && RandPos.y < 280) { // 700
			RandPos.y = rand() % 800 - 400;
		}

		EnemyPos->setPos(Krochi::Playerpos + RandPos);
		EnemyPos->setScale(Vector2(2.4f, 2.4f));

		EnemyCollider = AddComponent<Collider>();
		EnemyCollider->setCenter(Vector2(-7, -10));
		EnemyCollider->setSize(Vector2(50, 28)); // 50,28
		EnemyCollider->setRGB(0, 255, 0);

		EnemyAnimator->Play(L"RightWalk", true);

		eState = eEnemyState::Move;

		GameObject::Initialize();
	}
	void White_Fly::Update()
	{
		EnemyPos = GetComponent<Transform>();
		Ppos.x = Krochi::Playerpos.x;
		Ppos.y = Krochi::Playerpos.y;
		EnemyCollider->setRGB(0, 255, 0);
		movePos = EnemyPos->getPos();

		if (Damaged)
			eState = eEnemyState::Stun;

		if (monster_hp <= 0)
			eState = eEnemyState::Death;

		switch (eState)
		{
		case (eEnemyState::Move):
			Move();
			break;
		case (eEnemyState::Back_Move):
			Back_Move();
			break;
		case (eEnemyState::Stun):
			Stun();
			break;
		case (eEnemyState::Death):
			Death();
			break;
		case(eEnemyState::None):
			None();
			break;
		}

		EnemyPos->setPos(movePos);

		if (!Finded)
		{
			Distance = std::abs(Ppos.x - movePos.x) + std::abs(Ppos.y - movePos.y);

			if (Distance > 4000)
				EnemyPos->setPos(Krochi::Playerpos + RandPos);
		}

		GameObject::Update();
	}
	void White_Fly::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void White_Fly::Release()
	{
		GameObject::Release();
	}

	void White_Fly::Stun()
	{
		if (Ppos.x > movePos.x)
			EnemyAnimator->Play(L"Damaged_R", false);
		if (Ppos.x < movePos.x)
			EnemyAnimator->Play(L"Damaged_L", false);

		monster_hp -= Krochi::Power;
		Damaged = false;

		eState = eEnemyState::Back_Move;
	}

	void White_Fly::Move()
	{
		float vel = 80.f;

		if (Finded)
		{
			if (Ppos.x > movePos.x)
			{
				movePos.x += vel * Time::getDeltaTime();
				EnemyAnimator->Play_NO_RE(L"RightWalk", true);
			}
			if (Ppos.x < movePos.x)
			{
				movePos.x -= vel * Time::getDeltaTime();
				EnemyAnimator->Play_NO_RE(L"LeftWalk", true);
			}
			if (Ppos.y > movePos.y)
			{
				movePos.y += vel * Time::getDeltaTime();
			}
			if (Ppos.y < movePos.y)
			{
				movePos.y -= vel * Time::getDeltaTime();
			}
		}
	}


	void White_Fly::Back_Move()
	{
		delay += Time::getDeltaTime();

		if (delay >= 0.3f)
		{
			delay = 0.0f;
			eState = eEnemyState::Move;
		}

		float vel = 9.0f;

		if (Ppos.x > movePos.x)
			movePos.x -= vel * Time::getDeltaTime();
		if (Ppos.x < movePos.x)
			movePos.x += vel * Time::getDeltaTime();
		if (Ppos.y > movePos.y)
			movePos.y -= vel * Time::getDeltaTime();
		if (Ppos.y < movePos.y)
			movePos.y += vel * Time::getDeltaTime();
	}

	void White_Fly::Death()
	{
		lv_Item = object::Instantiate<Level_Item>
			(EnemyPos->getPos(), eLayerType::ITEMS);

		object::Destory(this);
	}

	void White_Fly::onCollisionStay(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Finded = true;
		}

		if (other->getOwner()->getName() == L"Enemy")
		{
			EnemyCollider->setRGB(255, 0, 0);
			otherEnemy = dynamic_cast<White_Fly*>(other->getOwner());

			if (otherEnemy->Distance < this->Distance)
				this->eState = eEnemyState::Back_Move;
			else
				this->eState = eEnemyState::Move;
		}
	}

	void White_Fly::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Finded = false;
		}

		if (other->getOwner()->getName() == L"Skill")
		{
			Damaged = true;

			mEffect = object::Instantiate<Effect>
				(EnemyPos->getPos() + Vector2(5.0f, 0.0f), eLayerType::EFFECT);
		}
	}
}