#include "pch.h"
#include "TextureActor.h"
#include "Manager\AssetManager.h"
#include "Resources\Texture.h"
#include "Utils\WinUtils.h"

TextureActor::TextureActor()
{
	bool load = GET_SINGLE(AssetManager)->LoadTexture(L"MP", L"Sprite\\UI\\Mp.bmp");
	if (load)
		_texture = GET_SINGLE(AssetManager)->GetTexture(L"MP");
}

TextureActor::~TextureActor()
{
}

void TextureActor::Init()
{
	Super::Init();
}

void TextureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void TextureActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_texture == nullptr)
		return;

	Vector2D pos = GetPos();
	Vector2D size = _texture->GetSize();

	// TransparentBlt�� �»�ܺ��� �׸��µ� ��ǥ�� �߾��� �ǵ��� ����
	pos -= size * 0.5f;

	::TransparentBlt(hdc,
		// �̹��� ��� ��ġ 
		(int32)pos.X,
		(int32)pos.Y,
		// ����� �̹����� ũ��
		(int32)size.X,
		(int32)size.Y,
		// �̹����� �ڵ�
		_texture->GetDC(),
		// �̹������� ������ �̹����� ��������
		0,
		0,
		// ������ �̹����� ũ��
		(int32)size.X,
		(int32)size.Y,
		_texture->GetTransparent());
}

void TextureActor::SetTexutre(std::shared_ptr<Texture> texture)
{
	if (!texture || _texture == texture)
		return;

	_texture = texture;
}
