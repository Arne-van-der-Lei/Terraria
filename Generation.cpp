//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Generation.h"

//#define GAME_ENGINE (GameEngine::GetSingleton())

Generation::Generation()
{
}

Generation::~Generation()
{
}

void Generation::Smooth(int less, int bigg, World* worldPtr) {

	for (size_t i = 0; i < Chunk::SIZE*World::WIDTH; i++) {
		for (size_t j = 0; j < Chunk::SIZE*World::HEIGHT; j++) {
			Chunk* chunkPtr = worldPtr->GetChunkAt((i / Chunk::SIZE), (j / Chunk::SIZE));
			int x = i - (i / Chunk::SIZE)*Chunk::SIZE;
			int y = j - (j / Chunk::SIZE)*Chunk::SIZE;

			int numberOfSides = checkSides(x, y, chunkPtr);

			if (numberOfSides > bigg) {
				if (chunkPtr->GetTileAt(x, y)->type != Chunk::Type::AIR)continue;
				GenerateTileAt(x, y, chunkPtr);
			} else if (numberOfSides < less) {
				chunkPtr->GetTileAt(x, y)->type = Chunk::Type::AIR;
			}
		}
	}
}

int Generation::checkSides(int x,int y, Chunk* chunkPtr) {
	int sides = 0;
	for (int i = x - 1; x + 1 >= i; i++) {
		for (int j = y - 1; y + 1 >= j; j++) {
			if (chunkPtr->GetTileAt(i, j) != nullptr) {
				if ((i != x || y != j) && chunkPtr->GetTileAt(i, j)->type != Chunk::Type::AIR) {
					sides++;
				}
			}
		}
	}
	return sides;
}

void Generation::GenerateChunk(World* worldPtr) {
	for (size_t i = 0; i < Chunk::SIZE*World::WIDTH; i++) {
		for (size_t j = 0; j < Chunk::SIZE*World::HEIGHT; j++) {
			Chunk* chunkPtr = worldPtr->GetChunkAt((i / Chunk::SIZE), (j / Chunk::SIZE));
			int x = i - (i / Chunk::SIZE)*Chunk::SIZE;
			int y = j - (j / Chunk::SIZE)*Chunk::SIZE;
			if(j < Chunk::SIZE * 3 && (rand() % 100)<20){
				GenerateTileAt(x, y, chunkPtr);
			}else if ((rand()% 100)<48) {
				chunkPtr->GetTileAt(x, y)->type = Chunk::Type::AIR;
			} else {
				GenerateTileAt(x, y, chunkPtr);
			}
		}
	}

	for (size_t i = 0; i < 5; i++) {
		Smooth(4, 4, worldPtr);
	}
	

	for (size_t i = 0; i < Chunk::SIZE*World::WIDTH; i++) {
		for (size_t j = 0; j < Chunk::SIZE*World::HEIGHT; j++) {
			Chunk* chunkPtr = worldPtr->GetChunkAt((i / Chunk::SIZE), (j / Chunk::SIZE));
			int x = i - (i / Chunk::SIZE)*Chunk::SIZE;
			int y = j - (j / Chunk::SIZE)*Chunk::SIZE;
			if (chunkPtr->GetTileAt(x, y)->type == Chunk::Type::DIRT) {
				chunkPtr->GetTileAt(x, y)->type = Chunk::Type::GRASS;
				j = 100000;
			}
		}
	}
}

void Generation::GenerateTileAt(int i, int j, Chunk* chunkPtr) {
	Tile * tilePtr = chunkPtr->GetTileAt(i, j);
	if (chunkPtr->GetY() *Chunk::SIZE + j < 2*Chunk::SIZE ){
		tilePtr->type = Chunk::Type::AIR;
    } else if (chunkPtr->GetY() *Chunk::SIZE + j >  3*Chunk::SIZE) {
		tilePtr->type = Chunk::Type::COBBLE;
	} else {
		tilePtr->type = Chunk::Type::DIRT;
	}

}