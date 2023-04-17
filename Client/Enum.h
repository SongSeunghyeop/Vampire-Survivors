#pragma once

enum class eSceneType
{
	Intro,
	Title,
	Play,
	Tool,
	Option,
	Ending,
	Max,
};

enum class eLayerType
{ // 그려지는 순서
	BACKGROUND,
	RADAR,
	ITEMS,
	PLAYERAFTER,
	PLAYER,
	ENEMYAFTER,
	ENEMY,
	EFFECT,
	SKILL,
	UI,
	ARROW,
	END,
};

enum class eComponentType
{
	TRANSFORM,
	COLLIDER,
	SPRITERENDERER,
	ANIMATOR,
	AUDIO,
	END,
};