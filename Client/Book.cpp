#include "Book.h"
#include "Book_Shadow.h"

namespace my
{
	Book::Book()
	{
		this->setName(L"Book");
		mTime = 0.0f;
	}
	Book::~Book()
	{

	}
	void Book::Initialize()
	{
		Skill_Image = ResourceManager::Load<Image>(L"Book", L"..\\Resources\\Book.bmp");

		Skil_Tr = GetComponent<Transform>();
		Skil_Tr->setScale(2.7, 2.7);
		Skill_Pos = Skil_Tr->getPos();

		Skill_Collider = AddComponent<Collider>();
		Skill_Collider->setCenter(Vector2(-2, -14));
		Skill_Collider->setSize(Vector2(31, 40));
		Skill_Collider->setRGB(0, 255, 0); 

		Skill_Animator = AddComponent<Animator>();
		Skill_Animator->CreateAnimation(L"Book", Skill_Image, Vector2::Zero, 1, 1, 1, 99.0f, 255, 0, 255);
		Skill_Animator->Play(L"Book", true);
		 
		shadow = object::Instantiate<Book_Shadow>(Krochi::getPlayerPos(),eLayerType::EFFECT);
		shadow->setBook(this);

		GameObject::Initialize();
	}
	void Book::Update()
	{
		dir = Vector2(500.0f, 500.0f);
		dir.Normalize();
		rotation = math::Rotate(dir, R);
		R += Time::getDeltaTime() * Skill_Vel;

		Skill_Pos.x = Krochi::getPlayerPos().x + distance * rotation.x ;
		Skill_Pos.y = Krochi::getPlayerPos().y + distance * rotation.y ;
		Skil_Tr->setPos(Skill_Pos);

		mTime += Time::getDeltaTime();

		if (mTime > sustain_time)
			object::Destory(this);

		GameObject::Update();
	}
	void Book::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Book::Release()
	{

	}
}
