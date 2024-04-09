#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Engine.h"
#include "World.h"

TilemapActor::TilemapActor()
{
	_tilemap = GET_SINGLE(AssetManager)->CreateTilemap(L"Tilemap_Basic");
	_tilemap->SetMapSize({ 63, 43 }); // Mapsize / tilesize => ���� tile ����(mapsize.X * mapsize.Y)
	_tilemap->SetTileSize(48);
	GET_SINGLE(AssetManager)->LoadTilemap(L"Tilemap_Basic", L"Tilemap\\Tilemap_basic_FINAL.txt");

	// Tile sprites
	{
		bool loadTexture = GET_SINGLE(AssetManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
		if (loadTexture)
		{
			_spriteO = GET_SINGLE(AssetManager)->CreateSprite(L"TileO", GET_SINGLE(AssetManager)->GetTexture(L"Tile"), { 0, 0 }, { 48, 48 });
			_spriteX = GET_SINGLE(AssetManager)->CreateSprite(L"TileX", GET_SINGLE(AssetManager)->GetTexture(L"Tile"), { 48, 0 }, { 48, 48 });
		}
	}
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::Init()
{
	Super::Init();
}

void TilemapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TickPicking();

	if (GET_SINGLE(InputManager)->GetEventDown(KeyType::P)) {
		GET_SINGLE(AssetManager)->SaveTilemap(L"Tilemap_Basic", L"Tilemap\\Tilemap_basic_FINAL.txt");
	}
	else if (GET_SINGLE(InputManager)->GetEventDown(KeyType::L)) {
		GET_SINGLE(AssetManager)->LoadTilemap(L"Tilemap_Basic", L"Tilemap\\Tilemap_basic_FINAL.txt");
	}
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr || _showDebug == false)
		return;

	const Vector2D mapSize = _tilemap->GetMapSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	// Culling : ���̴� �κи� ������
	const Vector2D halfScreenSize = Engine::GetScreenSize() * 0.5f;
	const Vector2D cameraPos = World::GetCameraPos();
	const Vector2D tileSize = { 1 / (float)TILE_SIZEX, 1 / (float)TILE_SIZEY };
	Vector2D pos = GetPos();

	// �������� �κ�
	Vector2D start = (cameraPos - halfScreenSize - pos) * tileSize;
	Vector2D end = (cameraPos + halfScreenSize - pos) * tileSize;

	pos = pos - (cameraPos - halfScreenSize);
	for (int32 y = (int32)start.Y; y <= (int32)end.Y; ++y) {
		for (int32 x = (int32)start.X; x <= (int32)end.X; ++x) {
			if (x < 0 || x >= (int32)mapSize.X || y < 0 || y >= (int32)mapSize.Y)
				continue;
		
			// ���� ��� �𼭸� ����
			switch (tiles[y][x].value) {
			case 0:
			{
				::TransparentBlt(hdc,
					static_cast<int32>(pos.X + x * TILE_SIZEX),
					static_cast<int32>(pos.Y + y * TILE_SIZEY),
					TILE_SIZEX,
					TILE_SIZEY,
					_spriteO->GetDC(),
					static_cast<int32>(_spriteO->GetSpritePos().X),
					static_cast<int32>(_spriteO->GetSpritePos().Y),
					TILE_SIZEX,
					TILE_SIZEY,
					_spriteO->GetTransparent());
			}
				break;
			case 1:
			{
				::TransparentBlt(hdc,
					static_cast<int32>(pos.X + x * TILE_SIZEX),
					static_cast<int32>(pos.Y + y * TILE_SIZEY),
					TILE_SIZEX,
					TILE_SIZEY,
					_spriteX->GetDC(),
					(int32)_spriteX->GetSpritePos().X,
					(int32)_spriteX->GetSpritePos().Y,
					TILE_SIZEX,
					TILE_SIZEY,
					_spriteX->GetTransparent());
			}
				break;
			}
		}
	}

}

void TilemapActor::TickPicking()
{
	if (GET_SINGLE(InputManager)->GetEventDown(KeyType::LeftMouse)) {
		const Vector2D cam = World::GetCameraPos();
		// ī�޶��� ��ǥ - ȭ���� ���� ũ�� (WinAPI�� ���� ��� �𼭸��� �������� �׸��⿡ ������ �������)
		const Vector2D screenPos = cam - Engine::GetScreenSize() * 0.5f; // ������ ȭ�� ��ǥ
		
		const Vector2D mousePos = GET_SINGLE(InputManager)->GetMousePos();

		// ���� ��ǥ
		Vector2D pos = mousePos + screenPos;
		// ���� ��ǥ���� ��� Tile�� pick�ߴ���
		pos *= Vector2D(1 / (float)TILE_SIZEX, 1 / (float)TILE_SIZEY);
		
		Tile* tile = _tilemap->GetTileAt(pos);
		if (tile) {
			// TODO : �������� Tile �� ����
 			tile->value = tile->value ^ 1; // 0�� 1 ������ �� �ְ� xor�� ��ȯ
		}
	}
}

Vector2D TilemapActor::ConvertToTilemapPos(Vector2D pos)
{
	if (_tilemap == nullptr)
		return Vector2D::Zero;

	int32 size = _tilemap->GetTileSize();
	const Vector2D tileSize = { 1 / (float)TILE_SIZEX, 1 / (float)TILE_SIZEY };

	Vector2D tilePos = pos * tileSize;
	tilePos.X = std::floorf(tilePos.X);
	tilePos.Y = std::floorf(tilePos.Y);

	return tilePos;
}