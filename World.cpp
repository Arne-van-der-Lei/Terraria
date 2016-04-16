//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "World.h"
#include "Chunk.h"
#include "Generation.h"
#include "Avatar.h"
#include "Filemanager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

World::World()
{
	for (size_t i = 0; i < WIDTH; i++) {
		for (size_t j = 0; j < HEIGHT; j++) {
			m_ChunkArrPtr.push_back(new Chunk(i,j,this));
		}
	}

	Generation::GenerateChunks(this);
	
	for (Chunk* chunkPtr : m_ChunkArrPtr) {
		chunkPtr->AfterInit();
	}
}

World::~World()
{
	for (Chunk* chunkPtr : m_ChunkArrPtr) {
		delete chunkPtr;
		chunkPtr = nullptr;
	}
}

void World::Tick(double deltaTime,Avatar* avatarPtr)
{

	/*if (GetChunkAt(avatarPtr->GetChunkPos().x - 3, avatarPtr->GetChunkPos().y) == nullptr) {
		generateNewChunkAt(avatarPtr->GetChunkPos().x - 3, avatarPtr->GetChunkPos().y);
	}
	if (GetChunkAt(avatarPtr->GetChunkPos().x + 3, avatarPtr->GetChunkPos().y) == nullptr) {
		generateNewChunkAt(avatarPtr->GetChunkPos().x + 3, avatarPtr->GetChunkPos().y);
	}*/
	int x = avatarPtr->GetChunkPos().x;
	int y = avatarPtr->GetChunkPos().y;

	for (size_t i = x - 3; i < x + 3; i++) {
		for (size_t j = y - 3; j < y + 3; j++) {
			if (GetChunkAt(i, j) != nullptr) {
				GetChunkAt(i, j)->Tick(deltaTime);
			}
		}
	}
}
void World::PaintBackground(Avatar* avatarPtr) {
	Chunk * chunkPtr = GetChunkAt(avatarPtr->GetChunkPos());
	int biome = chunkPtr->GetBiome();
	Bitmap* bmpBG1Ptr = FILE_MANAGER->GetBackgroundBitmap(biome * 3+1);
	Bitmap* bmpBG2Ptr = FILE_MANAGER->GetBackgroundBitmap(biome * 3+2);
	//Bitmap* bmpBG3Ptr = FILE_MANAGER->GetBackgroundBitmap(biome * 3+3);

	MATRIX3X2 matWorld, matWorld1, matWorld2, matTrans, matScale, matScale2, matScale3, matOffset, matOffset2;

	matTrans.SetAsTranslate(-avatarPtr->GetPosition()/(WIDTH*2));
	matOffset.SetAsTranslate(WIDTH*2, WIDTH * 2);
	matScale.SetAsScale(2);
	matScale.SetAsScale(1.7);
	matScale.SetAsScale(1.5);
	matWorld = matScale *matTrans;
	matWorld1 = matScale2 *matTrans*matOffset;
	matWorld2 = matScale3 *matTrans*matOffset*matOffset;

	GAME_ENGINE->SetWorldMatrix(matWorld);
	GAME_ENGINE->DrawBitmap(bmpBG1Ptr);
	GAME_ENGINE->SetWorldMatrix(matWorld2);
	GAME_ENGINE->DrawBitmap(bmpBG2Ptr);
	//GAME_ENGINE->SetWorldMatrix(matWorld);
	//GAME_ENGINE->DrawBitmap(bmpBG1Ptr);
}

void World::Paint(int x, int y)
{
	for (int i = x - 2; i < x + 3; i++) {
		for (int j = y - 2; j < y + 2; j++) {
			if (GetChunkAt(i, j) != nullptr) {
				GetChunkAt(i, j)->PaintBackground();
			}
		}
	}

	for (int i = x-2; i < x+3; i++) {
		for (int j = y-2; j < y+2; j++) {
			if (GetChunkAt(i, j) != nullptr) {
				GetChunkAt(i, j)->Paint();
			}
		}
	}
}

Chunk* World::GetChunkAt(int x, int y) {
	if (x < 0 || x > WIDTH-1 || y < 0 || y > HEIGHT-1)return nullptr;
	return m_ChunkArrPtr[x*HEIGHT + y];
}

Chunk* World::GetChunkAt(DOUBLE2 pos) {
	return GetChunkAt((int)pos.x, (int)pos.y);
}

std::vector<Chunk*> World::GetChunks() {
	return m_ChunkArrPtr;
}