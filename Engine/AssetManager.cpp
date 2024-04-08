#include "pch.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"

AssetManager::~AssetManager()
{
}

void AssetManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_resourcePath = fs::current_path().parent_path() / L"Resources";
}

bool AssetManager::LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent)
{
	// 이미 생생되어 있다면
	if (_textures.find(key) != _textures.end())
		return true;
	
	fs::path fullPath = _resourcePath / path;

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	if (!texture->LoadBmp(_hwnd, fullPath.c_str()))
		return false;

	texture->SetTransparent(transparent);
	_textures[key] = std::move(texture);

	return true;
}

std::shared_ptr<Texture> AssetManager::GetTexture(const std::wstring& key)
{
	if (_textures.find(key) == _textures.end())
	{
		::MessageBox(_hwnd, L"Texture needs to be loaded.", L"Texture does not exist.", NULL);
		return nullptr;
	}
	return _textures[key];
}

std::shared_ptr<Sprite> AssetManager::CreateSprite(const std::wstring& key, std::shared_ptr<Texture> texture, Vector2D spritePos, Vector2D spriteSize)
{
	if (texture == nullptr)
		return nullptr;

	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (spriteSize == Vector2D::Zero)
		spriteSize = texture->GetSize();

	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(texture, spritePos, spriteSize);
	_sprites[key] = std::move(sprite);

	return _sprites[key];
}

std::shared_ptr<Sprite> AssetManager::GetSprite(const std::wstring& key)
{
	if (_sprites.find(key) == _sprites.end()){
		::MessageBox(_hwnd, L"Sprite needs to be loaded.", L"Sprite does not exist.", NULL);
		return nullptr;
	}

	return _sprites[key];
}

std::shared_ptr<Flipbook> AssetManager::CreateFlipbook(const std::wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key];

	std::shared_ptr<Flipbook> flipbook = std::make_shared<Flipbook>();
	_flipbooks[key] = std::move(flipbook);

	return _flipbooks[key];
}

std::shared_ptr<Flipbook> AssetManager::GetFlipbook(const std::wstring& key)
{
	if (_flipbooks.find(key) == _flipbooks.end()) {
		::MessageBox(_hwnd, L"Flipbook needs to be created.", L"Flipbook does not exist.", NULL);
		return nullptr;
	}
		
	return _flipbooks[key];
}

bool AssetManager::LoadTilemap(const std::wstring& key, const std::wstring& path)
{
	std::shared_ptr<Tilemap> tilemap = nullptr;
	if (_tilemaps.find(key) == _tilemaps.end())
		_tilemaps[key] = std::make_shared<Tilemap>();
	
	tilemap = _tilemaps[key];

	fs::path fullPath = _resourcePath / path;
	if (!tilemap->LoadFile(fullPath)) {
		::MessageBox(_hwnd, L"Incorrect path or Tilemap file is not exist.", L"Tilemap loads fail.", NULL);
		return false;
	}

	return true;
}

void AssetManager::SaveTilemap(const std::wstring& key, const std::wstring& path)
{
	std::shared_ptr<Tilemap> tilemap = GetTilemap(key);

	fs::path fullPath = _resourcePath / path;
	tilemap->SaveFile(fullPath);
}

std::shared_ptr<Tilemap> AssetManager::CreateTilemap(const std::wstring& key)
{
	if (_tilemaps.find(key) != _tilemaps.end())
		return _tilemaps[key];

	std::shared_ptr<Tilemap> tilemap = std::make_shared<Tilemap>();
	_tilemaps[key] = std::move(tilemap);

	return _tilemaps[key];
}

std::shared_ptr<Tilemap> AssetManager::GetTilemap(const std::wstring& key)
{
	if (_tilemaps.find(key) == _tilemaps.end()) {
		::MessageBox(_hwnd, L"Tilemap needs to be loaded first.", L"Tilemap is not exist.", NULL);
		return nullptr;
	}

	return _tilemaps[key];
}
