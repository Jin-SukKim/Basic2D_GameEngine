#pragma once

class Texture;
class Sprite;
class Flipbook;

// Asset은 한번 Load한 뒤 공유해서 사용
class AssetManager
{
	GENERATE_SINGLE(AssetManager)
public:
	~AssetManager();
	void Init(HWND hwnd);

	void SetResourcePath(fs::path& path) { _resourcePath = path; }
	fs::path& GetResourcePath() { return _resourcePath; }


public:
	bool LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent = RGB(255, 0, 255) /* Default = RGB(255, 0, 255)*/);
	// TODO: shared_ptr vs weak_ptr?
	std::shared_ptr<Texture> GetTexture(const std::wstring& key);

	bool CreateSprite(const std::wstring& key, std::shared_ptr<Texture> texture, Vector2D pos = Vector2D::Zero, Vector2D size = Vector2D::Zero);
	std::shared_ptr<Sprite> GetSprite(const std::wstring& key);

private:
	HWND _hwnd;
	fs::path _resourcePath;

	std::unordered_map<std::wstring, std::shared_ptr<Texture>> _textures;
	std::unordered_map<std::wstring, std::shared_ptr<Sprite>> _sprites;
	std::unordered_map<std::wstring, std::shared_ptr<Flipbook>> _flipbooks;
};

