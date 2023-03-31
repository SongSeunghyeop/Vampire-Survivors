#pragma once
#include "myGameObject.h"
#include "myImage.h"

namespace my
{
	class TileMap_Tool : public GameObject
	{
	public:
		TileMap_Tool();
		TileMap_Tool(Vector2 pos);
		~TileMap_Tool();

		void InitializeTile(Image* atlas, int index);
		void SetIndex(int index);

		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Image* mAtlas;
		int mIndex;
		int mX;
		int mY;
	};
}
