//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "FileManager.h"
#include "World.h"
#include "Chunk.h"
#include "HUD.h"
#include "Avatar.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

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
	for (int i = 1; i < 5; i++) {
		m_BmpNPCArrPtr.push_back(new Bitmap(String("./Resources/NPC_") + String(i) + String(".png")));
	}
	for (int i = 1; i < 5; i++) {
		m_BmpItemArrPtr.push_back(new Bitmap(String("./Resources/Item_") + String(i) + String(".png")));
	}
	m_BmpHUDArrPtr.push_back(new Bitmap(String("./Resources/Inventory_Back.png")));
	m_BmpHUDArrPtr.push_back(new Bitmap(String("./Resources/font.png")));
	for (int i = 2; i < 16; i++) {
		m_BmpHUDArrPtr.push_back(new Bitmap(String("./Resources/Images/Inventory_Back") + String(i) + String(".png")));
	}
	m_BmpHUDArrPtr.push_back(new Bitmap(String("./Resources/Images/Heart.png")));
	m_BmpHUDArrPtr.at(1)->SetTransparencyColor(COLOR(100, 149, 237));
	m_BmpItemArrPtr.push_back(new Bitmap(String("./Resources/Item_1.png")));
	m_BmpItemArrPtr.push_back(new Bitmap(String("./Resources/Item_2.png")));
	m_BmpItemArrPtr.push_back(new Bitmap(String("./Resources/Item_3.png")));
	m_BmpItemArrPtr.push_back(new Bitmap(String("./Resources/Item_4.png")));
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
	for (Bitmap * bitmapPtr : m_BmpNPCArrPtr) {
		delete bitmapPtr;
		bitmapPtr = nullptr;
	}
	for (Bitmap * bitmapPtr : m_BmpItemArrPtr) {
		delete bitmapPtr;
		bitmapPtr = nullptr;
	}
	m_BmpArrPtr.clear();
	m_BmpWallArrPtr.clear();
	m_BmpBackgroundArrPtr.clear();
	m_BmpAvatarArrPtr.clear();
	m_BmpNPCArrPtr.clear();
	m_BmpItemArrPtr.clear();
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

Bitmap* FileManager::GetNPCBitmap(int number) {
	return m_BmpNPCArrPtr[number];
}

Bitmap* FileManager::GetItemBitmap(int number) {
	return m_BmpItemArrPtr[number-1];
}

Bitmap* FileManager::GetHUDBitmap(int number) {
	return m_BmpHUDArrPtr[number];
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

void FileManager::DrawString(String str,DOUBLE2 pos) {
	for (int i = 0; i < str.Length(); i++) {

		RECT2 rect;
		rect.left = (str.At(i)-48)*12;
		rect.right = (str.At(i) - 48 + 1) * 12;
		rect.top = 0;
		rect.bottom = 40;
		GAME_ENGINE->DrawBitmap(m_BmpHUDArrPtr.at(1),pos.x + i*8,pos.y,rect);
	}
}

void FileManager::LoadWorld(World* worldPtr) {
	std::ifstream file("./Resources/Saves/world.save");
	std::string data;
	std::string line;
	std::stringstream strStream;
	while (std::getline(file, line)) {
		strStream << line;
	}
	data = strStream.str();
	int chunkOffset = data.find("<chunk>");

	do {
		std::string ChunkString = data.substr(chunkOffset, data.find("</chunk>",chunkOffset)-chunkOffset);
		int x = GetIntFromString(ChunkString, "x");
		int y = GetIntFromString(ChunkString, "y");
		LoadChunk(worldPtr->GetChunkAt(x,y), ChunkString);
		chunkOffset = data.find("<chunk>", chunkOffset+1);
	} while (chunkOffset!= -1);
	
	file.close();
}

void FileManager::LoadChunk(Chunk* ChunkPtr,std::string str) {

	int tileOffset = str.find("<tile>");
	do {
		std::string tileString = str.substr(tileOffset,str.find("</tile>")- tileOffset);
		int x = GetIntFromString(tileString, "x");
		int y = GetIntFromString(tileString, "y");
		//std::cout << x << "," << y << std::endl;
		LoadTile(ChunkPtr->GetTileAt(x, y),tileString);
		tileOffset = str.find("<tile>", tileOffset+1);
	} while (tileOffset != -1);
}

void FileManager::LoadTile(Tile* tile,std::string str) {
	tile->air = GetIntFromString(str, "air");
	tile->type = GetIntFromString(str, "type");
	tile->backTileType = GetIntFromString(str, "background");
	tile->noBackround = GetIntFromString(str, "backgroundair");
}

void FileManager::LoadAvatar(Avatar* avatar, HUD* hud) {
	
}

void FileManager::SaveWorld(World* worldPtr) {
	std::stringstream strstream;
	strstream << "<world>\n<width>" << World::WIDTH << "</width>\n"
		               << "<height>" << World::HEIGHT << "</height>\n";

	for (int i = 0; i < World::WIDTH; i++){
		for (int j = 0; j < World::HEIGHT; j++) {
			strstream << SaveChunk(worldPtr->GetChunkAt(i, j));
		}
	}

	strstream << "</world>\n";

	std::ofstream file("./Resources/Saves/world.save");
	file << strstream.str();
	file.close();
}

void FileManager::SaveAvatar(Avatar* avatarPtr, HUD* HUDPtr) {
	std::stringstream strstream;

	strstream << avatarPtr->ToString() << std::endl;
	strstream << HUDPtr->ToString() << std::endl;
	std::ofstream file("./Resources/Saves/avatar.save");
	file << strstream.str();
	file.close();
}

std::string FileManager::SaveChunk(Chunk* chunkPtr) {
	std::string str = "<chunk>\n";
	str += "<x>" + std::to_string(chunkPtr->GetX()) + "</x>\n"
	   + "<y>" + std::to_string(chunkPtr->GetY()) + "</y>\n"
	   + "<biome>" + std::to_string(chunkPtr->GetBiome()) + "</biome>\n";
	for (int i = 0; i < Chunk::SIZE; i++) {
		for (int j = 0; j < Chunk::SIZE; j++) {
			str += SaveTile(chunkPtr->GetTileAt(i, j));
		}
	}
	str += "</chunk>\n";
	return str;
}

std::string FileManager::SaveTile(Tile* tilePtr) {
	std::string str = "<tile>\n";
	str += "<x>" + std::to_string(tilePtr->x) + "</x>\n"
		+ "<y>" + std::to_string(tilePtr->y) + "</y>\n"
		+ "<type>" + std::to_string(tilePtr->type) + "</type>\n"
		+ "<air>" + std::to_string(tilePtr->air) + "</air>\n"
		+ "<background>" + std::to_string(tilePtr->backTileType) + "</background>\n"
		+ "<backgroundair>" + std::to_string(tilePtr->noBackround) + "<backgroundair>\n"
		+ "</tile>\n";
	return str;
}

int FileManager::GetIntFromString(std::string strSource,std::string value ) {
	int begin = strSource.find("<" + value + ">") + value.length() + 2;
	int end = strSource.find("</" + value + ">") - begin;
	return std::stoi(strSource.substr(begin,end ));
}