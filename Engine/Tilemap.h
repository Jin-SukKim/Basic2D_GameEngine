#pragma once

struct Tile {
	// TODO: 타일에 들어갈 정보 (ex: objectType, tileType etc)
	int32 value = 0;
};

class Tilemap
{
public:
	Tilemap();
	~Tilemap();

	bool LoadFile(const std::wstring& path);
	void SaveFile(const std::wstring& path);

	bool CanGo(Vector2D cellPos);
public:
	// Mapsize / tilesize => 맵의 tile 개수(mapsize.x * mapsize.y)
	void SetMapSize(const Vector2D& size);
	Vector2D GetMapSize() const {	return _mapSize; }
	
	void SetTileSize(const int32& size) { _tileSize = size; }
	int32 GetTileSize() const { return _tileSize; }
	
	Tile* GetTileAt(const Vector2D& pos);
	std::vector<std::vector<Tile>>& GetTiles() { return _tiles; }

private:
	Vector2D _mapSize = {};
	int32 _tileSize = {};
	std::vector<std::vector<Tile>> _tiles;
};

