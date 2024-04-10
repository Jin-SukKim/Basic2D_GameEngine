#pragma once

// enum class가 아니므로 int로도 사용 가능
enum LayerType {
	LT_BACKGROUND,
	LT_OBJECT,
	LT_EFFECT,
	LT_UI,

	LT_MAXCOUNT
};

enum class LevelType {
	LEVEL_DEFAULT,
	LEVEL_GAME,
	LEVEL_EDIT
};

enum Dir {
	DIR_Up,
	DIR_Down,
	DIR_Left,
	DIR_Right,
};

enum class ActionState {
	AS_Idle,
	AS_Move,
	AS_Attack,
};

enum class ColliderType {
	CT_Square,
	CT_Circle
};

// TODO: C++의 Bitmask를 enum class를 활용해 사용할때
// https://stackoverflow.com/questions/12059774/c11-standard-conformant-bitmasks-using-enum-class
// https://voithos.io/articles/enum-class-bitmasks/
// https://walbourn.github.io/modern-c++-bitmask-types/
enum CollisionLayerType : uint8 
{
	CLT_None = (1u << 0), // 1u = unsinged int
	CLT_Object = (1u << 1),
	CLT_Character = (1u << 2),
	CLT_Projectile = (1u << 3),
	CLT_Trace = (1u << 4),
};