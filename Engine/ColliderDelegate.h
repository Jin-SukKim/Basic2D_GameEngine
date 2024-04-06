#pragma once

class Collider;

//class OverlapDelegate {
//	void operator()(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
//		std::shared_ptr<Actor> owner = _owner.lock();
//		if (owner == nullptr)
//			return;
//
//		// 스마트 포인터는 pointer-to-member-access operator가 없어 멤버 함수에 접근하기 위해선 dereference한뒤 사용해야된다.
//		((*owner).*_func)(comp, other, otherComp);
//	}
//	
//	template<typename T>
//	void BindDelegate(std::weak_ptr<T> owner, void(T::*func)(std::weak_ptr<Collider>, std::weak_ptr<T>, std::weak_ptr<Collider>)) {
//		std::shared_ptr<Actor> ownerActor = owner.lock();
//		if (ownerActor == nullptr || func == nullptr)
//		{
//			// TODO: Log
//			return;
//		}
//
//		_func = *func;
//		_owner = ownerActor;
//	}
//
//private:
//	std::weak_ptr<Actor> _owner;
//	std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)> _func = nullptr;
//};

class Delegate {
public:
	void operator()(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
		_callBack(comp, other, otherComp);
	}

	template<typename T>
	void BindDelegate(std::weak_ptr<T> object, void(T::* func)(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)) {
		_callBack = [object, func](std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
			std::shared_ptr<T> owner = object.lock();
			if (owner == nullptr)
				return;
			((*owner).*func)(comp, other, otherComp);
		};
	}	
	
	template<typename T>
	void BindDelegateTest(T* object, void(T::* func)()) {
		_testCall = [object, func]() {
			(object->*func)();
		};
	}

	template<typename T>
	void BindDelegateTestSmartPtr(T* object, void(T::* func)()) {
		_testCall = [object, func]() {
			std::shared_ptr<T> owner = object.lock();
			if (owner == nullptr)
				return;
			((*owner).*func)();
		};
	}

private:
	std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)> _callBack;
	std::function<void(void)> _testCall = nullptr;

};