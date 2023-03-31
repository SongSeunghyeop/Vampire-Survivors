#include "TileMap_Tool.h"
#include "myTransform.h"
#include "myCamera.h"

namespace my
{
	TileMap_Tool::TileMap_Tool()
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{
	}

	TileMap_Tool::TileMap_Tool(Vector2 pos)
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{
		GetComponent<Transform>()->setPos(pos);
	}

	TileMap_Tool::~TileMap_Tool()
	{
	}

	void TileMap_Tool::InitializeTile(Image* atlas, int index)
	{
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;

		mAtlas = atlas;
		SetIndex(index);
	}

	void TileMap_Tool::SetIndex(int index)
	{
		int maxCol = mAtlas->GetWidth() / TILE_SIZE_X;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE_Y;

		mY = index / maxCol;
		mX = index % maxCol;
	}

	void TileMap_Tool::Update()
	{
	}

	void TileMap_Tool::Render(HDC hdc)
	{
		if (mAtlas == nullptr || mIndex < 0)
			return;

		Transform* tr = GetComponent<Transform>();

		Vector2 renderPos = Camera::CaluatePos(tr->getPos());

		TransparentBlt(hdc
			, renderPos.x, renderPos.y
			, TILE_SIZE_X, TILE_SIZE_Y
			, mAtlas->GetHdc()
			, TILE_SIZE_X * mX, TILE_SIZE_Y * mY
			, TILE_SIZE_X, TILE_SIZE_X
			, RGB(255, 0, 255));
	}

}
