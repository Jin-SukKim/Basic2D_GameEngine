#pragma once

class Collider;
class Actor;

struct OverlapDelegate {
	template<typename T>
	void BindDelegate(T* owner, void(T::* func)(Collider, Actor, Collider)) {
		_owner = dynamic_cast<Actor>(owner);
		_func = func;

		if (_owner == nullptr && _func == nullptr)
		{

		}
	}

	Actor* _owner = nullptr;
	std::function<void(Actor&, Collider, Actor, Collider)> _func = nullptr;
};