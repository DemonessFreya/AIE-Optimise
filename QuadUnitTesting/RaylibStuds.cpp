#include "pch.h"

// Define dummy/stub structures if needed by raylib headers included in headers
struct Color { unsigned char r, g, b, a; };
struct Texture2D { unsigned int id; int width; int height; int mipmaps; int format; };

// Provide dummy implementations for the Raylib functions called by Draw() methods
extern "C" {
    void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
        // Do nothing in unit tests
    }

    void DrawTexture(Texture2D texture, int posX, int posY, Color tint) {
        // Do nothing in unit tests
    }
}