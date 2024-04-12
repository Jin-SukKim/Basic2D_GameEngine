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


#define GENERATE_BODY(className, parent)	\
	using Super = parent;					\
public:										\
	className();							\
	virtual ~className() override;					