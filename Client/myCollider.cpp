#include "myCollider.h"
#include "myTransform.h"
#include "myGameObject.h"

namespace my
{
	UINT Collider::ColliderNumber = 0;

	Collider::Collider()
		: Component(eComponentType::COLLIDER)
		, mCenter(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(53.0f, 69.0f)
		,mRgb(0,255,0)
		, mID(ColliderNumber++)
	{

	}
	Collider::~Collider()
	{

	}
	 
	void Collider::Initialize()
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		mPos = tr->getPos() +mCenter;
 	}
	void Collider::Update()
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		mPos = tr->getPos() +mCenter;
	}

	void Collider::Render(HDC hdc)
	{
		//HPEN pen = CreatePen(BS_SOLID, 1, RGB(mRgb.r, mRgb.g, mRgb.b));	
		//HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		//HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		//Vector2 pos = Camera::CaluatePos(mPos);
		//Rectangle(hdc, pos.x , pos.y, pos.x + mSize.x, pos.y + mSize.y);

		//(HPEN)SelectObject(hdc, oldPen);
		//(HBRUSH)SelectObject(hdc, oldBrush);
		//DeleteObject(pen);

	}
	void Collider::Release()
	{
		
	}

	void Collider::onCollisionEnter(Collider* other)
	{
		getOwner()->onCollisionEnter(other);
	}
	void Collider::onCollisionStay(Collider* other)
	{
		getOwner()->onCollisionStay(other);
	}
	void Collider::onCollisionExit(Collider* other)
	{
		getOwner()->onCollisionExit(other);
	}
}
