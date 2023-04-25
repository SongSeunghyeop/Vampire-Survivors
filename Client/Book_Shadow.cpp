#include "Book_Shadow.h"

namespace my
{
	Book_Shadow::Book_Shadow()
	{
		this->setName(L"Ax&Book");
		mTime = 0.0f;
	}
	Book_Shadow::~Book_Shadow()
	{

	}
	void Book_Shadow::Initialize()
	{
		shadow_Image = ResourceManager::Load<Image>(L"Book_Shadow", L"..\\Resources\\Book3.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->setScale(2.1, 2.1);
		tr->setPos(Krochi::getPlayerPos());

		Shadow_Animator = AddComponent<Animator>();
		Shadow_Animator->CreateAnimation(L"Book_Shadow", shadow_Image, Vector2::Zero, 3, 1, 3, 0.2f, 255, 0, 255);
		Shadow_Animator->Play(L"Book_Shadow", true);

		GameObject::Initialize();
	}
	void Book_Shadow::Update()
	{
		Transform* tr = GetComponent<Transform>();
		tr->setPos(book->Skill_Pos - Vector2(5, 20));

		mTime += Time::getDeltaTime();

		if (mTime > book->sustain_time + 0.1f)
		{
			object::Destory(this);
		}
		GameObject::Update();
	}
	void Book_Shadow::Render(HDC hdc)
	{	 
		GameObject::Render(hdc);
	}
	void Book_Shadow::Release()
	{

	}
}
