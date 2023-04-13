#include "myResourceManager.h"
#include "Boss.h"
#include "Time.h"
#include "Effect.h"
#include "myObject.h"
#include "EnemyManager.h"
#include "Boss_Skill.h"
#include "Boss_After.h"

namespace my
{
	Vector2 Boss::movePos;
	float Boss::Boss_vel;
	Boss::eBossState Boss::eState;

	Boss::Boss()
	{
		Entity::setName(L"Enemy");
	}
	Boss::~Boss()
	{

	}

	void Boss::Initialize()
	{
		Boss_R = ResourceManager::Load<Image>(L"Boss_R", L"..\\Resources\\Boss_R.bmp");
		Boss_L = ResourceManager::Load<Image>(L"Boss_L", L"..\\Resources\\Boss_L.bmp");
		bDamaged_R = ResourceManager::Load<Image>(L"bDamaged_R", L"..\\Resources\\Boss_Damaged_R.bmp");
		bDamaged_L = ResourceManager::Load<Image>(L"bDamaged_L", L"..\\Resources\\Boss_Damaged_L.bmp");
		//Boss_Die_R = ResourceManager::Load<Image>(L"Boss_Die_R", L"..\\Resources\\Boss_Die_R.bmp");
		//Boss_Die_L = ResourceManager::Load<Image>(L"Boss_Die_L", L"..\\Resources\\Boss_Die_L.bmp");
	
		BossAnimator = AddComponent<Animator>();
		BossAnimator ->CreateAnimation(L"Boss_MoveR", Boss_R, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);
		BossAnimator ->CreateAnimation(L"Boss_MoveL", Boss_L, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);

		BossAnimator ->CreateAnimation(L"Boss_IdleR", Boss_R, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);
		BossAnimator ->CreateAnimation(L"Boss_IdleL", Boss_L, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);

		BossAnimator ->CreateAnimation(L"bDamaged_R", bDamaged_R, Vector2::Zero, 1, 1, 1, 0.15f, 255, 0, 255);
		BossAnimator ->CreateAnimation(L"bDamaged_L", bDamaged_L, Vector2::Zero, 1, 1, 1, 0.15f, 255, 0, 255);

		//EnemyAnimator->CreateAnimation(L"Boss_DieR", Boss_Die_R, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		//EnemyAnimator->CreateAnimation(L"Boss_DieL", Boss_Die_L, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);

		Boss_TR = GetComponent<Transform>();
		Boss_TR->setScale(Vector2(3.3f, 3.3f));

		BossCollider = AddComponent<Collider>();
		BossCollider->setRGB(0, 255, 0);
		BossCollider->setCenter(Vector2(-8, -28));
		BossCollider->setSize(Vector2(100, 130));

		BossAnimator->Play(L"Boss_MoveR", true);
		boss_hp = 9999;
		Boss_vel = 280;
		//
		eState = eBossState::Move;

		for (int i = 0; i < 4; i++)
		{
			Boss_After* shadow = 
				object::Instantiate<Boss_After>(Boss_TR->getPos(), eLayerType::ENEMYAFTER);
			shadow->setShadowDistance(20.0f - i * 5);
		}

		GameObject::Initialize();
	}
	void Boss::Update()
	{
		skill_Time += Time::getDeltaTime();

		BossCollider->setRGB(0, 255, 0);
		Boss_TR = GetComponent<Transform>();
		Ppos = Krochi::getPlayerPos();
		movePos = Boss_TR->getPos();

		switch (eState)
		{
		case (eBossState::Move):
			move();
			break;
		case (eBossState::Back_Move):
			back_move();
			break;
		case (eBossState::Death):
			death();
			break;
		case (eBossState::Attack):
			attack();
			break;
		}
		Boss_TR->setPos(movePos);

		if (skill_Time >= 4.5f)
			eState = eBossState::Attack;

		GameObject::Update();
	}
	void Boss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Boss::Release()
	{
		GameObject::Release();
	}

	void Boss::attack()
	{
		Boss_Skill* m1
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-280.0f, -500.0f), eLayerType::SKILL);
		Boss_Skill* m2
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-200.0f, -500.0f), eLayerType::SKILL);
		Boss_Skill* m3
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-120.0f,-450.0f), eLayerType::SKILL);
		Boss_Skill* m4
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-40.0f, -400.0f), eLayerType::SKILL);
		Boss_Skill* m5
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(40.0f, -400.0f), eLayerType::SKILL);
		Boss_Skill* m6
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(120.0f, -450.0f), eLayerType::SKILL);
		Boss_Skill* m7
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(200.0f, -500.0f), eLayerType::SKILL);
		Boss_Skill* m8
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(280.0f, -500.0f), eLayerType::SKILL);
		
		eState = eBossState::Move;
		skill_Time = 0.0f;
	}

	void Boss::move()
	{
		movePos += (Ppos - Boss_TR->getPos()).Normalize() * Boss_vel * Time::getDeltaTime();

		if (Ppos.x - 10 > movePos.x)
			BossAnimator->Play_NO_RE(L"Boss_MoveR", true);

		if (Ppos.x + 10 < movePos.x)
			BossAnimator->Play_NO_RE(L"Boss_MoveL", true);
	}

	void Boss::back_move()
	{
		delay += Time::getDeltaTime();

		if (Ppos.x - 10 > movePos.x)
			BossAnimator->Play_NO_RE(L"bDamaged_R", true);

		if (Ppos.x + 10 < movePos.x)
			BossAnimator->Play_NO_RE(L"bDamaged_L", true);

		if (delay >= 0.15f)
		{
			delay = 0.0f;

			if (boss_hp <= 0)
				eState = eBossState::Death;
			else
				eState = eBossState::Move;
		}
	}
	void Boss::death()
	{
		if (Ppos.x > movePos.x)
		{

		}
		if (Ppos.x < movePos.x)
		{
	
		}
	}

	void Boss::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Book")
		{
			BossCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Boss_TR->getPos() + Vector2(20.0f, 0.0f), eLayerType::EFFECT);

			boss_hp -= Krochi::getPlayerPower(L"Book");
			this->eState = eBossState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Cross")
		{
			BossCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Boss_TR->getPos() + Vector2(20.0f, 0.0f), eLayerType::EFFECT);
			boss_hp -= Krochi::getPlayerPower(L"Cross");
			this->eState = eBossState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Lightning")
		{
			BossCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Boss_TR->getPos() + Vector2(20.0f, 0.0f), eLayerType::EFFECT);
			boss_hp -= Krochi::getPlayerPower(L"Lightning");
			this->eState = eBossState::Back_Move;
		}
	}

	void Boss::onCollisionStay(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Boss_vel = 280.0f;
		}
		if (other->getOwner()->getName() == L"Player")
		{
			Boss_vel = 0.0f;
		}
	}

	void Boss::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Boss_vel = 0.0f;
			skill_Time -= 8.0f;
		}
	}
}