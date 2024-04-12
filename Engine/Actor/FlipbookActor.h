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
	// Animation�� ������ Ȯ��
	bool IsAnimationEnded();
	// TODO: ���� �ð��� ������ Animation�� ����Ȱɷ� �Ǵ��� ���� �ִ�.
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

