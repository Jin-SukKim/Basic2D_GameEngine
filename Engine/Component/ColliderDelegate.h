#pragma once

class Collider;

//class OverlapDelegate {
//	void operator()(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
//		std::shared_ptr<Actor> owner = _owner.lock();
//		if (owner == nullptr)
//			return;
//
//		// ����Ʈ �����ʹ� pointer-to-member-access operator�� ���� ��� �Լ��� �����ϱ� ���ؼ� dereference�ѵ� ����ؾߵȴ�.
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

	// Collider Component�� owner object�� ������� Manager Ŭ�������� ���� ������� �����Ƿ�
	// raw pointer�� this�� ����ص� �� �� ����.
	template<typename T>
	void BindDelegate(T* object, void(T::* func)(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)) {
		_callBack = [object, func](std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
			(object->*func)(comp, other, otherComp);
		};
	}	
	
	// ���� �⺻
	template<typename T>
	void BindDelegateTest(T* object, void(T::* func)()) {
		// ������ std::bind�� ���� �������� Lambda�� ��� �Լ� ����
		_testCall = [object, func]() {
			(object->*func)();
		};
	}

	// Parameter�� ����
	template<typename T>
	void BindDelegateTestParam(T* object, void(T::* func)(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)) {
		_testCall_param = [object, func](std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp) {
			(object->*func)(comp, other, otherComp);
			};
	}

	// ��� �Լ��� owner object�� ����Ʈ �����ͷ� �޾ƺ��� 
	// Function Pointer�� �Ҵ��� Function�� ���� Ŭ������ cast������Ѵ�. (dynamic_pointer_cast)
	// �ƴϸ� �Լ��� ���� Ŭ������ ����Ʈ �������� this�� �θ��� �ְ� inherit�ϸ� �ȴ�.
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
	// parameter : �ڱ��ڽ��� component, �浹�� Actor, �浹�� Actor�� Component
	std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)> _callBack;
	std::function<void(void)> _testCall = nullptr;
	std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Actor>, std::weak_ptr<Collider>)> _testCall_param = nullptr;

};