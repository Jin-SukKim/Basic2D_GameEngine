#pragma once
#include "Actor.h"
class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	// Animation이 끝날걸 확인
	bool IsAnimationEnded();
	// TODO: 일정 시간이 지나면 Animation이 종료된걸로 판단할 수도 있다.
	// bool IsAnimationEnded(float time);
public:
	void SetFlipbook(std::shared_ptr<Flipbook> flipbook);

private:
	void Reset();

protected:
	std::shared_ptr<Flipbook> _flipbook;
	float _sumTime = 0.f;
	int32 _idx = 0;
};

