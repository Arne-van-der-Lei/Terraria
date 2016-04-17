//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "FileManager.h"

//#define GAME_ENGINE (GameEngine::GetSingleton())

FileManager* FileManager::m_FileManagerPtr = nullptr;

void FileManager::GetAllTextures() {
	m_BmpArrPtr.push_back(new Bitmap(String("./Resources/Tile_00.png")));
	m_BmpArrPtr.push_back(new Bitmap(String("./Resources/Tile_01.png")));
	m_BmpArrPtr.push_back(new Bitmap(String("./Resources/Tile_02.png")));
	m_BmpWallArrPtr.push_back(new Bitmap(String("./Resources/Wall_01.png")));
	m_BmpBackgroundArrPtr.push_back(new Bitmap(String("./Resources/Background_0.png")));
	m_BmpBackgroundArrPtr.push_back(new Bitmap(String("./Resources/Background_114.png")));
	m_BmpBackgroundArrPtr.push_back(new Bitmap(String("./Resources/Background_115.png")));
	m_BmpBackgroundArrPtr.push_back(new Bitmap(String("./Resources/Background_116.png")));
	m_BmpBackgroundArrPtr.push_back(new Bitmap(String("./Resources/Background_168.png")));
	m_BmpBackgroundArrPtr.push_back(new Bitmap(String("./Resources/Background_169.png")));
	m_BmpBackgroundArrPtr.push_back(new Bitmap(String("./Resources/Background_170.png")));
	for (int i = 0; i < 14; i++) {
		m_BmpAvatarArrPtr.push_back(new Bitmap(String("./Resources/Player_0_") + String(i) + String(".png")));
	}
}

FileManager::~FileManager() {
	for (Bitmap * bitmapPtr : m_BmpArrPtr) {
		delete bitmapPtr;
		bitmapPtr = nullptr;
	}

	for (Bitmap * bitmapPtr : m_BmpWallArrPtr) {
		delete bitmapPtr;
		bitmapPtr = nullptr;
	}

	for (Bitmap * bitmapPtr : m_BmpBackgroundArrPtr) {
		delete bitmapPtr;
		bitmapPtr = nullptr;
	}

	for (Bitmap * bitmapPtr : m_BmpAvatarArrPtr) {
		delete bitmapPtr;
		bitmapPtr = nullptr;
	}
	m_BmpArrPtr.clear();
	m_BmpWallArrPtr.clear();
	m_BmpBackgroundArrPtr.clear();
	m_BmpAvatarArrPtr.clear();
}

FileManager::FileManager() {	
	GetAllTextures();
}

Bitmap* FileManager::GetBitmap(int number) {
	return m_BmpArrPtr[number-1];
}

Bitmap* FileManager::GetWallBitmap(int number) {
	return m_BmpWallArrPtr[number-1];
}

Bitmap* FileManager::GetBackgroundBitmap(int number) {
	return m_BmpBackgroundArrPtr[number];
}

Bitmap* FileManager::GetAvatarBitmap(int number) {
	return m_BmpAvatarArrPtr[number];
}

FileManager* FileManager::GetSingleton() {
	if (m_FileManagerPtr == nullptr) {
		m_FileManagerPtr = new FileManager();
	}
	return m_FileManagerPtr;
}

void FileManager::RemoveAllTextures() {
	delete m_FileManagerPtr;
	m_FileManagerPtr = nullptr;
}