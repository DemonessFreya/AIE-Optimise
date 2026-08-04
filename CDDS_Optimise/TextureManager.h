#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>

class TextureManager
{
private:
	std::unordered_map<std::string, Texture2D> m_textures;

public:
	TextureManager();
	~TextureManager();

	Texture2D GetTexture(const std::string& filename);

	void Clear();
};
