#pragma once

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

	virtual void Init() {}
	virtual void Tick(float DeltaTime) {}
	virtual void Render(HDC hdc) {}

public: // Getter/Setter
	ObjectType GetType() const { return _type; }
	
	void SetPos(const Vector2D& pos) { _pos = pos;	};
	Vector2D GetPos() const { return _pos; }

	void SetTag(std::string tag) { _tag = tag; }
	std::string GetTag() {	return _tag; }
protected:
	ObjectType _type;
	Vector2D _pos = { 0.f, 0.f };

private:
	std::string _tag = "";
};

