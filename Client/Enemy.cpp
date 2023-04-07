#include "myResourceManager.h"
#include "Enemy.h"
#include "Time.h"
#include "Effect.h"
#include "myObject.h"
#include "Level_Item.h"

namespace my
{
	bool Enemy::Finded;

	Enemy::Enemy()
	{
		Entity::setName(L"Enemy");
		vel_type1 = 100.0f;
		vel_type2 = 120.0f;
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::Initialize()
	{
		EnemyR_Img = ResourceManager::Load<Image>(L"EnemyR", L"..\\Resources\\Fly_R_All.bmp");
		EnemyL_Img = ResourceManager::Load<Image>(L"EnemyL", L"..\\Resources\\Fly_L_All.bmp");
		Damaged_R = ResourceManager::Load<Image>(L"Damaged_R", L"..\\Resources\\Damaged_R.bmp");
		Damaged_L = ResourceManager::Load<Image>(L"Damaged_L", L"..\\Resources\\Damaged_L.bmp");
		zDamaged_R = ResourceManager::Load<Image>(L"zDamaged_R", L"..\\Resources\\Zombie_Damaged_R.bmp");
		zDamaged_L = ResourceManager::Load<Image>(L"zDamaged_L", L"..\\Resources\\Zombie_Damaged_L.bmp");
		Die_R = ResourceManager::Load<Image>(L"fly_Die_R", L"..\\Resources\\fly_Die_R.bmp");
		Die_L = ResourceManager::Load<Image>(L"fly_Die_L", L"..\\Resources\\fly_Die_L.bmp");
		//
		Zombie_R = ResourceManager::Load<Image>(L"Zombie_R", L"..\\Resources\\Zombie_Move_R.bmp");
		Zombie_L = ResourceManager::Load<Image>(L"Zombie_L", L"..\\Resources\\Zombie_Move_L.bmp");
		Zombie_Die_R = ResourceManager::Load<Image>(L"Zombie_Die_R", L"..\\Resources\\Zombie_Die_R.bmp");
		Zombie_Die_L = ResourceManager::Load<Image>(L"Zombie_Die_L", L"..\\Resources\\Zombie_Die_L.bmp");



		// ----- Black_Fly
		EnemyAnimator = AddComponent<Animator>();
		EnemyAnimator->CreateAnimation(L"RightWalk", EnemyR_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"LeftWalk", EnemyL_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Idle_R", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Idle_L", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Damaged_R", Damaged_R, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Damaged_L", Damaged_L, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"fly_Die_R", Die_R, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"fly_Die_L", Die_L, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		//
		// ----- Zombie
		EnemyAnimator->CreateAnimation(L"Zombie_MoveR", Zombie_R, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_MoveL", Zombie_L, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Zombie_IdleR", Zombie_R, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_IdleL", Zombie_L, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"zDamaged_R", zDamaged_R, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"zDamaged_L", zDamaged_L, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Zombie_DieR", Zombie_Die_R, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_DieL", Zombie_Die_L, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		//
		Enemy_TR = GetComponent<Transform>();
		EnemyCollider = AddComponent<Collider>();
		EnemyCollider->setRGB(0, 255, 0);

		//랜덤 타입
		int TypeNum = rand() % 10; // 0 ~ 9

		if (TypeNum < 4) //0 ~ 3
			eType = eEnemyType::ZOMBIE;

		else // 4 ~ 9
			eType = eEnemyType::BLACK;

		if (TypeNum > 0 && TypeNum < 9) // 80%
			Finded = true;
		//

		// 타입에 따른 생성 정보
		switch (eType)
		{
		case(eEnemyType::BLACK):
		{
			EnemyAnimator->Play(L"RightWalk", true);
			monster_hp = 70;
			Enemy_vel = vel_type1;
			Enemy_TR->setScale(Vector2(2.4f, 2.4f));
			EnemyCollider->setCenter(Vector2(-7, -10));
			EnemyCollider->setSize(Vector2(50, 28)); // 50,28
		}
			break;
		case(eEnemyType::ZOMBIE):
		{
			EnemyAnimator->Play(L"Zombie_MoveR", true);
			monster_hp = 100;
			Enemy_vel = vel_type2;
			Enemy_TR->setScale(Vector2(2.0f, 2.0f));
			EnemyCollider->setCenter(Vector2(-10, -22));
			EnemyCollider->setSize(Vector2(47,55)); // 50,70
		}
			break;
		}
		//
		eState = eEnemyState::Move;

		GameObject::Initialize();
	}
	void Enemy::Update()
	{
		Enemy_TR = GetComponent<Transform>();
		Ppos = Krochi::getPlayerPos(); 
		EnemyCollider->setRGB(0, 255, 0);
		prevPos = Enemy_TR->getPos();
		movePos = prevPos;
		switch (eState)
		{
		case (eEnemyState::Move):
			move();
			break;
		case (eEnemyState::Back_Move):
			back_move();
			break;
		case (eEnemyState::Slow):
			slow();
			break;
		case (eEnemyState::Death):
			death();
			break;
		case(eEnemyState::None):
			none();
			break;
		}
		Enemy_TR->setPos(movePos);

		Distance =
			std::abs(Ppos.x - movePos.x) + std::abs(Ppos.y - movePos.y);

		if (Distance > 3000) // 플레이어와의 거리가 멀어진다면, 위치를 가까이 옮겨줌
			Enemy_TR->setPos(Krochi::getPlayerPos() + Init_Pos);

		GameObject::Update();
	}
	void Enemy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Enemy::Release()
	{
		GameObject::Release();
	}

	void Enemy::move()
	{
		if (Enemy::Finded)
		{
			movePos += (Ppos - Enemy_TR->getPos()).Normalize() * Enemy_vel * Time::getDeltaTime();

			if (Ppos.x - 5 > movePos.x)
			{ 
				if(eType == eEnemyType::BLACK)
					EnemyAnimator->Play_NO_RE(L"RightWalk", true);
				if(eType == eEnemyType::ZOMBIE)
					EnemyAnimator->Play_NO_RE(L"Zombie_MoveR", true);
			}	

			if (Ppos.x + 5 < movePos.x)
			{
				if (eType == eEnemyType::BLACK)
					EnemyAnimator->Play_NO_RE(L"LeftWalk", true);

				if (eType == eEnemyType::ZOMBIE)
					EnemyAnimator->Play_NO_RE(L"Zombie_MoveL", true);
			}
		}
	}

	void Enemy::slow()
	{
		delay += Time::getDeltaTime();

		if (delay >= 0.2f)
		{
			delay = 0.0f;

			if (monster_hp <= 0)
				eState = eEnemyState::Death;
			else
				eState = eEnemyState::Move;
		}
		movePos = prevPos;
	}

	void Enemy::back_move()
	{
		delay += Time::getDeltaTime();

		float vel = -200.0f;
		movePos += (Ppos - Enemy_TR->getPos()).Normalize() * vel * Time::getDeltaTime();

		
		if (Ppos.x - 5 > movePos.x)
		{
			if (eType == eEnemyType::BLACK)
				EnemyAnimator->Play_NO_RE(L"Damaged_R", true);
			if(eType == eEnemyType::ZOMBIE)
				EnemyAnimator->Play_NO_RE(L"zDamaged_R", true);
		}
		if (Ppos.x + 5 < movePos.x)
		{
			if (eType == eEnemyType::BLACK)
				EnemyAnimator->Play_NO_RE(L"Damaged_L", true);
			if (eType == eEnemyType::ZOMBIE)
				EnemyAnimator->Play_NO_RE(L"zDamaged_L", true);
		}

		if (delay >= 0.15f)
		{
			if (monster_hp <= 0)
				eState = eEnemyState::Death;
			else
				eState = eEnemyState::Move;
		}
	}
	void Enemy::death()
	{
		if (Ppos.x > movePos.x)
		{
		if (eType == eEnemyType::BLACK)
			EnemyAnimator->Play_NO_RE(L"fly_Die_R", false);
		if (eType == eEnemyType::ZOMBIE)
			EnemyAnimator->Play_NO_RE(L"Zombie_DieR", false);
		}
		if (Ppos.x < movePos.x)
		{
		if (eType == eEnemyType::BLACK)
			EnemyAnimator->Play_NO_RE(L"fly_Die_L", false);
		if (eType == eEnemyType::ZOMBIE)
			EnemyAnimator->Play_NO_RE(L"Zombie_DieL", false);
		}
	
		if (EnemyAnimator->IsComplete())
		{
			lv_Item = object::Instantiate<Level_Item>
				(Enemy_TR->getPos(), eLayerType::ITEMS);
			object::Destory(this);
		}
	}

	void Enemy::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Enemy")
		{
			EnemyCollider->setRGB(255, 0, 0);
			otherEnemy = dynamic_cast<Enemy*>(other->getOwner());

			eState = eEnemyState::Slow;
		}
		if (other->getOwner()->getName() == L"Ax&Book")
		{
			EnemyCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Enemy_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);

			this->eState = eEnemyState::Back_Move;
			monster_hp -= Krochi::getPlayerPower();
		}
	}

	void Enemy::onCollisionStay(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			Enemy_vel = 0.0f;
		}
		if (other->getOwner()->getName() == L"Radar")
		{
			Enemy::Finded = true;
		}
		if (other->getOwner()->getName() == L"Skill")
		{
			EnemyCollider->setRGB(255, 0, 0);

			if (other->getOwner()->getState() == GameObject::eState::Death)
			{
				mEffect = object::Instantiate<Effect>
					(Enemy_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);
				this->eState = eEnemyState::Back_Move;
				monster_hp -= Krochi::getPlayerPower();
			}
		}
	}

	void Enemy::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Enemy::Finded = false;
		}
		if (other->getOwner()->getName() == L"Player")
		{
			if (eType == eEnemyType::BLACK)
				Enemy_vel = vel_type1;
			if (eType == eEnemyType::ZOMBIE)
				Enemy_vel = vel_type2;
		}
	}
}