#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "World.h"
#include "Engine.h"

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::Init()
{
	Super::Init();
}

void FlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_flipbook == nullptr)
		return;

	if (IsAnimationEnded())
		return;

	_sumTime += DeltaTime;

	// Sprite Animation�� Play�� Time
	const FlipbookInfo& info = _flipbook->GetInfo();
	int32 frameCount = (info.end - info.start + 1); // Animation Sprite ��
	float delta = info.duration / frameCount; // Animaiont �� play �ð� / Animation Sprite ��

	if (_sumTime >= delta)
	{
		_idx = _idx + 1;
		if (_idx >= frameCount)
			Reset();
		else
			_sumTime = 0.f;
	}
}


void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();

	Vector2D pos = GetPos();
	Vector2D size = info.spriteSize;
	Vector2D cameraPos = World::GetCameraPos();
	// TransparentBlt�� �»�ܺ��� �׸��µ� ��ǥ�� �߾��� �ǵ��� ����
	pos = pos - size * 0.5f - (cameraPos - Engine::GetScreenSize() * 0.5f);


	::TransparentBlt(hdc,
		// �̹��� ��� ��ġ 
		static_cast<int32>(pos.X),
		static_cast<int32>(pos.Y),
		// ����� �̹����� ũ��
		static_cast<int32>(size.X),
		static_cast<int32>(size.Y),
		// �̹����� �ڵ�
		info.texture->GetDC(),
		// �̹������� ������ �̹����� ��������
		static_cast<int32>((info.start + _idx) * size.X),
		static_cast<int32>(info.line * size.Y),
		// ������ �̹����� ũ��
		static_cast<int32>(size.X),
		static_cast<int32>(size.Y),
		info.texture->GetTransparent()
	);
}

bool FlipbookActor::IsAnimationEnded()
{
	if (_flipbook == nullptr)
		return true;

	const FlipbookInfo& info = _flipbook->GetInfo();
	// Loop�� ���� ��� sprite�� play������
	if (info.loop == false && _idx == info.end)
		return true;

	return false;
}

void FlipbookActor::SetFlipbook(std::shared_ptr<Flipbook> flipbook)
{
	if (!flipbook || _flipbook == flipbook)
		return;

	_flipbook = flipbook;
	Reset();
}


void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}
