#include "Boss_After.h"

namespace my
{
	Boss_After::Boss_After()
	{
		Entity::setName(L"Enemy");
	}
	Boss_After::~Boss_After()
	{

	}

	void Boss_After::Initialize()
	{
		Boss_R = ResourceManager::Load<Image>(L"Shadow_R", L"..\\Resources\\Boss_Shadow_R.bmp");
		Boss_L = ResourceManager::Load<Image>(L"Shadow_L", L"..\\Resources\\Boss_Shadow_L.bmp");
		//Boss_Die_R = ResourceManager::Load<Image>(L"Boss_Die_R", L"..\\Resources\\Boss_Die_R.bmp");
		//Boss_Die_L = ResourceManager::Load<Image>(L"Boss_Die_L", L"..\\Resources\\Boss_Die_L.bmp");
	
		BossAnimator = AddComponent<Animator>();
		BossAnimator->CreateAnimation(L"Shadow_MoveR", Boss_R, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);
		BossAnimator->CreateAnimation(L"Shadow_MoveL", Boss_L, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);

		BossAnimator->CreateAnimation(L"Shadow_IdleR", Boss_R, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);
		BossAnimator->CreateAnimation(L"Shadow_IdleL", Boss_L, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);

		//EnemyAnimator->CreateAnimation(L"Boss_DieR", Boss_Die_R, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		//EnemyAnimator->CreateAnimation(L"Boss_DieL", Boss_Die_L, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);

		After_TR = GetComponent<Transform>();
		After_TR->setScale(Vector2(3.3f, 3.3f));

		BossAnimator->Play(L"Shadow_MoveR", true);
		//
		eState = eAfterState::Move;

		GameObject::Initialize();
	}
	void Boss_After::Update()
	{
		skill_Time += Time::getDeltaTime();
		After_TR = GetComponent<Transform>();
		Ppos = Krochi::getPlayerPos();
		afterPos = After_TR->getPos();

		switch (eState)
		{
		case (eAfterState::Move):
			move();
			break;
		case(eAfterState::None):
			none();
			break;
		}

		After_TR->setPos(afterPos);

		GameObject::Update();
	}
	void Boss_After::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Boss_After::Release()
	{
		GameObject::Release();
	}

	void Boss_After::move()
	{
		Transform* tr = GetComponent<Transform>();
		afterPos = After_TR->getPos();

		if (afterPos.x <  Boss::movePos.x - shadow_distance)
			afterPos.x += Boss::Boss_vel * Time::getDeltaTime();

		if (afterPos.x > Boss::movePos.x + shadow_distance)
			afterPos.x -= Boss::Boss_vel * Time::getDeltaTime();

		if (afterPos.y < Boss::movePos.y - shadow_distance)
			afterPos.y += Boss::Boss_vel * Time::getDeltaTime();

		if (afterPos.y > Boss::movePos.y + shadow_distance)
			afterPos.y -= Boss::Boss_vel * Time::getDeltaTime();

		if (afterPos.x < Boss::movePos.x - 5)
			BossAnimator->Play_NO_RE(L"Shadow_MoveR", true);
		else if(afterPos.x > Boss::movePos.x + 5)
			BossAnimator->Play_NO_RE(L"Shadow_MoveL", true);

		tr->setPos(afterPos);

	}
}