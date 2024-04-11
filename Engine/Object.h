#pragma once
#include "AssetManager.h"

enum class ObjectType {
	Object,
	Actor,
	Component
};

class Object
{
public:
	Object(ObjectType type = ObjectType::Object);
	virtual ~Object();

	virtual void Init() = 0;
	virtual void Tick(float DeltaTime) = 0;
	virtual void Render(HDC hdc) = 0;

	/*
		UE의 C++에서 Asset 가져와 사용하기
		static ConstructorHelper::FObjectFinder<UStaticMesh> SM_TEMP(TEXT("path"));
		if (SM_TEMP.Succeeded())
			TempComponent->SetStaticMehs(SM_TEMP.Object);

		TODO: Asset에 Asset이 있으면 가져와 등록하고 Component에 넘겨주기
		TODO: Template으로 한 함수로 모든 타입을 가져올 수 있게 하기 (어떻게?)

		(type-trait를 사용하면 가능할수도, ex: std::is_convertiable<> 변환가능 한지 확인)
	*/

public: // Getter/Setter
	ObjectType GetType() const { return _type; }
	
	virtual void SetPos(const Vector2D& pos) { _pos = pos; };
	virtual Vector2D GetPos() const { return _pos; }
	
	void SetSize(const Vector2D& size) { _size = size; };
	Vector2D GetSize() const { return _size; }

	void SetName(std::wstring name) { _name = name; }
	std::wstring GetName() { return _name; }

	void SetTag(std::wstring tag) { _tag = tag; }
	std::wstring GetTag() {	return _tag; }

	void SetLayer(LayerType layer) { _layer = layer; }
	LayerType GetLayer() const { return _layer; }

private:
	ObjectType _type;
	Vector2D _pos = { 0.f, 0.f };
	Vector2D _size = Vector2D::One;
	std::wstring _name = L"";
	std::wstring _tag = L"";

	LayerType _layer = LayerType::LT_OBJECT;
};
