#pragma once

#define GENERATE_SINGLE(className)		\
private:								\
	className() {}						\
public:									\
	static className* GetInstance()		\
	{									\
		static className s_instance;	\
		return &s_instance;				\
	}									

#define GET_SINGLE(className) className::GetInstance()
