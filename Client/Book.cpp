#include "Book.h"
#include "Time.h"
#include "myObject.h"
#include "Krochi.h"
#include "Book_Shadow.h"

namespace my
{
	Book::Book()
		: mTime(0.0f)
		, effect_Time(0.0f)
	{
		this->setName(L"Book");
	}
	Book::~Book()
	{

	}
	void Book::Initialize()
	{
		book_Image = ResourceManager::Load<Image>(L"Book", L"..\\Resources\\Book.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->setScale(2.7, 2.7);
		bookPos = tr->getPos();

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(-2, -14));
		collider->setSize(Vector2(31, 40));
		collider->setRGB(0, 255, 0); 

		Ax_Animator = AddComponent<Animator>();
		Ax_Animator->CreateAnimation(L"Book", book_Image, Vector2::Zero, 1, 1, 1, 99.0f, 255, 0, 255);
		Ax_Animator->Play(L"Book", true);
		 
		shadow = object::Instantiate<Book_Shadow>(Krochi::getPlayerPos(),eLayerType::EFFECT);
		shadow->setBook(this);

		GameObject::Initialize();
	}
	void Book::Update()
	{
		/*float x = cosf(-PI / 4.0f);
		float y = sinf(-PI / 4.0f);*/
		//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
		//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);

		dir = Vector2(500.0f, 500.0f);
		dir.Normalize();
		rotation = math::Rotate(dir, R);
		R += Time::getDeltaTime() * book_vel;

		Transform* tr = GetComponent<Transform>();
		bookPos.x = Krochi::getPlayerPos().x + distance * rotation.x ;
		bookPos.y = Krochi::getPlayerPos().y + distance * rotation.y ;
		tr->setPos(bookPos);

		mTime += Time::getDeltaTime();

		if (mTime > book_Time)
		{
			object::Destory(this);
		}

		GameObject::Update();
	}
	void Book::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Book::Release()
	{

	}
	void Book::onCollisionEnter(Collider* other)
	{

	}

	void Book::onCollisionStay(Collider* other)
	{

	}

	void Book::onCollisionExit(Collider* other)
	{

	}
}
