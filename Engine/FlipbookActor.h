#pragma once
#include "Actor.h"
class Flipbook;

class FlipbookActor : public Actor
{
	GENERATE_BODY(FlipbookActor, Actor)
public:

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	bool IsAnimationStarted();
	bool IsAnimationAtIdx(int32 index);
	// Animation이 끝날걸 확인
	bool IsAnimationEnded();
	// TODO: 일정 시간이 지나면 Animation이 종료된걸로 판단할 수도 있다.
	// bool IsAnimationEnded(float time);
public:
	void SetFlipbook(std::shared_ptr<Flipbook> flipbook);
	std::shared_ptr<Flipbook> GetFlipbook() const { return _flipbook; }

	void SetInfo(const struct FlipbookInfo& info);
	void Reset();

protected:
	float _sumTime = 0.f;
	int32 _idx = 0;

private:
	std::shared_ptr<Flipbook> _flipbook;
};

