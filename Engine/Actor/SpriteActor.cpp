#include "pch.h"
#include "SpriteActor.h"
#include "Manager\AssetManager.h"
#include "Resources\Sprite.h"
#include "World\World.h"
#include "Engine.h"

SpriteActor::SpriteActor()
{
	bool load = GET_SINGLE(AssetManager)->LoadTexture(L"Map", L"Sprite\\Map\\Stage01.bmp");
	if (load) {
		_sprite = GET_SINGLE(AssetManager)->CreateSprite(L"Map", GET_SINGLE(AssetManager)->GetTexture(L"Map"));
		SetLayer(LT_BACKGROUND);
		SetSize(_sprite->GetSpriteSize());
	}
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::Init()
{
	Super::Init();

	SetPos(GetPos() + _sprite->GetSpriteSize() * 0.5f);
}

void SpriteActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr)
		return;

	Vector2D pos = GetPos();
	Vector2D size = _sprite->GetSpriteSize();
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
		_sprite->GetDC(),
		// �̹������� ������ �̹����� ��������
		static_cast<int32>(_sprite->GetSpritePos().X),
		static_cast<int32>(_sprite->GetSpritePos().Y),
		// ������ �̹����� ũ��
		static_cast<int32>(size.X),
		static_cast<int32>(size.Y),
		_sprite->GetTransparent()
	);
}

void SpriteActor::SetSprite(std::shared_ptr<Sprite> sprite)
{ 
	if (!sprite || _sprite == sprite)
		return;

	_sprite = sprite;
}

