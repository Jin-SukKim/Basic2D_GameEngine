#pragma once

class Texture;

// Asset�� �ѹ� Load�� �� �����ؼ� ���
class AssetManager
{
	GENERATE_SINGLE(AssetManager)
public:
	~AssetManager();
	void Init(HWND hwnd);

	fs::path& GetResourcePath() { return _resourcePath; }


public:
	bool LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent = RGB(255, 0, 255) /* Default = RGB(255, 0, 255)*/);
	std::shared_ptr<Texture> GetTexture(const std::wstring& key);

private:
	HWND _hwnd;
	fs::path _resourcePath;

	std::unordered_map<std::wstring, std::shared_ptr<Texture>> _textures;
};
