#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "AssetManager.h"
#include "Sprite.h"
#include "Engine.h"

TilemapActor::TilemapActor()
{
	bool load = GET_SINGLE(AssetManager)->LoadTilemap(L"Tilemap_Basic", L"Tilemap\\Tilemap_Basic.txt");
	if (load) {
		bool loadTexture = GET_SINGLE(AssetManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
		if (loadTexture)
		{
			_spriteO = GET_SINGLE(AssetManager)->CreateSprite(L"TileO", GET_SINGLE(AssetManager)->GetTexture(L"Tile"), { 0, 0 }, { 48, 48 });
			_spriteX = GET_SINGLE(AssetManager)->CreateSprite(L"TileX", GET_SINGLE(AssetManager)->GetTexture(L"Tile"), { 48, 0 }, { 48, 48 });
		}

		_tilemap = GET_SINGLE(AssetManager)->CreateTilemap(L"Tilemap_Basic");
		_tilemap->SetMapSize({ 63, 43 }); // Mapsize / tilesize => 맵의 tile 개수(mapsize.X * mapsize.Y)
		_tilemap->SetTileSize(48);
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
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr || _showDebug == false)
		return;

	const Vector2D mapSize = _tilemap->GetMapSize();
	const int32 tileSize = _tilemap->GetTileSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	// Culling : 보이는 부분만 렌더링
	Vector2D halfScreenSize = Engine::GetScreenSize() * 0.5f;
	const Vector2D pos = GetPos();

	Vector2D start = (-halfScreenSize) - pos;
	start.X /= static_cast<int32>(TILE_SIZEX);
	start.Y /= static_cast<int32>(TILE_SIZEY);
	
	Vector2D end = (halfScreenSize) - pos;
	end.X /= static_cast<int32>(TILE_SIZEX);
	end.Y /= static_cast<int32>(TILE_SIZEY);

	for (int32 y = (int32)start.Y; y <= (int32)end.Y; ++y) {
		for (int32 x = (int32)start.X; x <= (int32)end.X; ++x) {
			if (x < 0 || x >= (int32)mapSize.X || y < 0 || y >= (int32)mapSize.Y)
				continue;
		
			// 왼쪽 상단 모서리 기준
			switch (tiles[y][x].value) {
			case 0:
			{
				::TransparentBlt(hdc,
					static_cast<int32>(pos.X + x * TILE_SIZEX + halfScreenSize.X),
					static_cast<int32>(pos.Y + y * TILE_SIZEY + halfScreenSize.Y),
					TILE_SIZEX,
					TILE_SIZEY,
					_spriteO->GetDC(),
					static_cast<int32>(_spriteO->GetSpritePos().X + halfScreenSize.X),
					static_cast<int32>(_spriteO->GetSpritePos().Y + halfScreenSize.Y),
					TILE_SIZEX,
					TILE_SIZEY,
					_spriteO->GetTransparent());
			}
				break;
			case 1:
			{
				::TransparentBlt(hdc,
					(int32)pos.X + x * static_cast<int32>(TILE_SIZEX),
					(int32)pos.Y + y * static_cast<int32>(TILE_SIZEY),
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
}
