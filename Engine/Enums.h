#pragma once

// enum class�� �ƴϹǷ� int�ε� ��� ����
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