#include "pch.h"
#include "AssetManager.h"
#include "Texture.h"

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
