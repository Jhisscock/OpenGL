#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <Windows.h>

class TextureLoader {
	public:
		unsigned char* textureData;
		int iWidth, iHeight;
		TextureLoader(const char*);
		~TextureLoader();
	private:
		BITMAPFILEHEADER bfh;
		BITMAPINFOHEADER bih;
};
#endif