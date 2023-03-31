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
{ // �׷����� ����
	BACKGROUND,
	RADAR,
	ITEMS,
	PLAYERAFTER,
	PLAYER,
	ENEMY,
	EFFECT,
	UI,
	SKILL,
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