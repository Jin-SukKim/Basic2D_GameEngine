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
		if (_callBack)
			_callBack(comp, other, otherComp);
	}

	// Collider Component는 owner object가 사라질때 Manager 클래스에서 같이 사라지게 했으므로
	// raw pointer인 this를 사용해도 될 것 같다.
	template<typename T>
	void BindDelegate(T* object, void(T::* func)(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)) {
		_callBack = [object, func](std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
			(object->*func)(comp, other, otherComp);
		};
	}	
	
	// 가장 기본
	template<typename T>
	void BindDelegateTest(T* object, void(T::* func)()) {
		// 일종의 std::bind와 같은 성능으로 Lambda로 멤버 함수 저장
		_testCall = [object, func]() {
			(object->*func)();
		};
	}

	// Parameter를 포함
	template<typename T>
	void BindDelegateTestParam(T* object, void(T::* func)(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)) {
		_testCall_param = [object, func](std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
			(object->*func)(comp, other, otherComp);
			};
	}

	// 멤버 함수의 owner object를 스마트 포인터로 받아보기 
	// Function Pointer에 할당할 Function을 가진 클래스로 cast해줘야한다. (dynamic_pointer_cast)
	// 아니면 함수를 가진 클래스가 스마트 포인터의 this를 부를수 있게 inherit하면 된다.
	template<typename T>
	void BindDelegateTestSmartPtr(std::shared_ptr<T> object, void(T::* func)()) {
		_testCall = [object, func]() {
			std::shared_ptr<T> owner = object.lock();
			if (owner == nullptr)
				return;
			((*owner).*func)();
		};
	}


private:
	// parameter : 자기자신의 component, 충돌한 Actor, 충돌한 Actor의 Component
	std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)> _callBack;
	std::function<void(void)> _testCall = nullptr;
	std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)> _testCall_param = nullptr;

};