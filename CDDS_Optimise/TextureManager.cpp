#include "TextureManager.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {
	Clear();
}

Texture2D TextureManager::GetTexture(const std::string& filename) {
	// search map for for filename
	auto iterator = m_textures.find(filename);

	// if found, return existing texture
	if (iterator != m_textures.end()) {
		return iterator->second;
	}

	// if not found, load from drive
	Texture2D newTexture = LoadTexture(filename.c_str());

	// save to map
	m_textures[filename] = newTexture;

	// return new texture
	return newTexture;
}

void TextureManager::Clear() {
	// loop through all stored textures and unload from gpu
	for (auto& pair : m_textures) {
		UnloadTexture(pair.second);
	}

	// empty dictionary
	m_textures.clear();
}
