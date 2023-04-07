#include "Book_Shadow.h"
#include "Time.h"
#include "myObject.h"
#include "Krochi.h"

namespace my
{
	Book_Shadow::Book_Shadow()
		: mTime(0.0f)
		, effect_Time(0.0f)
	{
		this->setName(L"Ax&Book");
		bullet_vel = 120.0f;

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
		/*float x = cosf(-PI / 4.0f);
		float y = sinf(-PI / 4.0f);*/
		//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
		//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);

		Transform* tr = GetComponent<Transform>();
		tr->setPos(book->bookPos - Vector2(5, 20));

		mTime += Time::getDeltaTime();

		if (mTime > book->book_Time + 0.1f)
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
