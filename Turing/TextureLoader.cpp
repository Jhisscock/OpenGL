#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "TextureLoader.h"
#include <stdio.h>
#include <iostream>

//Takes a bmp image and extracts the data for use in a texture
TextureLoader::TextureLoader(const char* filename) {
	FILE* file = 0;
	file = fopen(filename, "rb");
	if (!file) {
		std::cout << "Couldn't find file" << std::endl;
	}
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
	if (bfh.bfType != 0x4d42) {
		std::cout << "Not a valid file" << std::endl;
	}
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);
	if (bih.biSizeImage == 0) {
		bih.biSizeImage = bih.biHeight * bih.biWidth * 3;
	}
	textureData = new unsigned char[bih.biSizeImage];
	fseek(file, bfh.bfOffBits, SEEK_SET);
	fread(textureData, 1, bih.biSizeImage, file);
	unsigned char tmp;
	for (int i = 0; i < bih.biSizeImage; i += 3) {
		tmp = textureData[i];
		textureData[i] = textureData[i + 2];
		textureData[i + 2] = tmp;
	}
	iWidth = bih.biWidth;
	iHeight = bih.biHeight;
	fclose(file);
}

TextureLoader::~TextureLoader() {
	delete[] textureData;
}