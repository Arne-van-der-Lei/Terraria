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
//#define GAME_ENGINE (GameEngine::GetSingleton())

World::World()
{
	for (size_t i = 0; i < WIDTH; i++) {
		for (size_t j = 0; j < HEIGHT; j++) {
			m_ChunkArrPtr.push_back(new Chunk(i,j,this));
		}
	}

	Generation::GenerateChunk(this);
	
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