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
	m_BmpArrPtr.push_back(nullptr);
	m_BmpArrPtr.push_back(new Bitmap(String("./Resources/Tile_00.png")));
	m_BmpArrPtr.push_back(new Bitmap(String("./Resources/Tile_01.png")));
	m_BmpArrPtr.push_back(new Bitmap(String("./Resources/Tile_02.png")));
	m_BmpWallArrPtr.push_back(new Bitmap(String("./Resources/Wall_01.png")));
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

	m_BmpArrPtr.clear();
	m_BmpWallArrPtr.clear();
}

FileManager::FileManager() {	
	GetAllTextures();
}

Bitmap* FileManager::GetBitmap(int number) {
	return m_BmpArrPtr[number];
}

Bitmap* FileManager::GetWallBitmap(int number) {
	return m_BmpWallArrPtr[number];
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