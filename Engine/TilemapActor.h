#pragma once
#include "Actor.h"

class Tilemap;

enum TILE_SIZE {
	TILE_WIDTH = 63,
	TILE_HEIGHT = 43,
	TILE_SIZEX = 48,
	TILE_SIZEY = 48
};

class TilemapActor : public Actor
{
	GENERATE_BODY(TilemapActor, Actor)
public:

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	void TickPicking();

	// Tilemap 기반의 좌표로 변환 
	Vector2D ConvertToTilemapPos(Vector2D pos);
	Vector2D GetCellPos(const Vector2D& cellPos);
public:
	void SetTilemap(std::shared_ptr<Tilemap> tilemap) { _tilemap = tilemap;	}
	std::shared_ptr<Tilemap> GetTilemap() {return _tilemap; }

	void SetShowDebug(bool showDebug) { _showDebug = showDebug; }
private:
	// TODO: 왠만하면 Component로 바꿔주기
	std::shared_ptr<Tilemap> _tilemap;
	std::shared_ptr<Sprite> _spriteX;
	std::shared_ptr<Sprite> _spriteO;
	bool _showDebug = false;
};

