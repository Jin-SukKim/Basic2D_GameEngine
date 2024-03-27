#pragma once

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

// enum class가 아니므로 int로도 사용 가능
enum LAYER_TYPE {
	LT_BACKGROUND,
	LT_OBJECT,
	LT_EFFECT,
	LT_UI,

	LT_MAXCOUNT
};