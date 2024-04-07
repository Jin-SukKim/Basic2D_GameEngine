#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

bool Tilemap::LoadFile(const std::wstring& path)
{
	// txt ���Ͽ� ����
	{
		std::wifstream ifs;

		ifs.open(path, std::ios::out); // ������ ������ �����
		if (ifs.fail())
			return false;

		Vector2D mapSize = Vector2D::Zero;
		ifs >> mapSize.X >> mapSize.Y;

		SetMapSize(mapSize);

		for (int32 y = 0; y < mapSize.Y; ++y) {
			std::wstring line;
			ifs >> line;

			for (int32 x = 0; x < mapSize.X; ++x)
				_tiles[y][x].value = line[x] - L'0';
		}

		ifs.close();
	}

	return true;
}

void Tilemap::SaveFile(const std::wstring& path)
{
	// Txt ����
	{
		std::wofstream ofs;

		ofs.open(path);

		ofs << _mapSize.X << std::endl;
		ofs << _mapSize.Y << std::endl;

		for (int32 y = 0; y < _mapSize.Y; ++y) {
			for (int32 x = 0; x < _mapSize.X; ++x)
				ofs << _tiles[y][x].value;
			ofs << std::endl;
		}

		ofs.close();
	}
}

bool Tilemap::CanGo(Vector2D cellPos)
{
	if (_tiles.empty())
		return false;

	Tile* tile = GetTileAt(cellPos);
	if (tile == nullptr)
		return false;

	// TODO: Tile struct�̳� TileInfo struct/bit�� ���� �����ϰ� parameter�� �޾�
	// �����ִ��� Ȯ���� ������ ����ϱ�

	// ����� ���� �ƴ����� Ȯ��
	return tile->value != 1;
}

// Mapsize / tilesize => ���� tile ����(mapsize.x * mapsize.y)
void Tilemap::SetMapSize(const Vector2D& size)
{
	_mapSize = size;

	_tiles = std::vector<std::vector<Tile>>(static_cast<int32>(size.Y), std::vector<Tile>(static_cast<int32>(size.X)));

	for (int32 y = 0; y < size.Y; ++y)
		for (int32 x = 0; x < size.X; ++x)
			_tiles[y][x] = Tile{ 0 };
}

Tile* Tilemap::GetTileAt(const Vector2D& pos)
{
	if (pos.X < 0 || pos.X >= _mapSize.X || pos.Y < 0 || pos.Y >= _mapSize.Y)
		return nullptr;

	return &_tiles[static_cast<int32>(pos.Y)][static_cast<int32>(pos.X)];
}

