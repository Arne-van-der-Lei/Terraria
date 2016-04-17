//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "LandNPC.h"
#include "Chunk.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

LandNPC::LandNPC(DOUBLE2 pos, DOUBLE2 size): NPC( pos, size) {
	m_isOnGround = false;

}

LandNPC::~LandNPC() {}

void LandNPC::Tick(double deltaTime) {}

void LandNPC::Paint() {}

void LandNPC::DoCollision(World* world, double deltaTime) {

	int toprightX = (int)(m_pos.x - m_size.x / 2.0);
	int toprightY = (int)(m_pos.y - m_size.y / 2.0);

	Chunk* chunkPtr = world->GetChunkAt(toprightX / (Chunk::TILESIZE*Chunk::SIZE), toprightY / (Chunk::TILESIZE*Chunk::SIZE));

	if (chunkPtr == nullptr) {
		m_motion.y += 1 * deltaTime;
		return;
	}

	int blockposX = toprightX / (Chunk::TILESIZE) - chunkPtr->GetX()*Chunk::SIZE;
	int blockposY = toprightY / (Chunk::TILESIZE) - chunkPtr->GetY()*Chunk::SIZE;

	for (int i = blockposX; i < blockposX + (int)ceil(m_size.x / Chunk::TILESIZE) + 1; i++) {
		for (int j = blockposY; j < blockposY + (int)ceil(m_size.y / Chunk::TILESIZE) + 1; j++) {

			Tile* tilePtr = chunkPtr->GetTileAt(i, j);
			double topRightLocX = toprightX - chunkPtr->GetX()* Chunk::TILESIZE* Chunk::SIZE;
			double topRightLocY = toprightY - chunkPtr->GetY()* Chunk::TILESIZE* Chunk::SIZE;

			if (tilePtr != nullptr) {
				if (tilePtr->type != Chunk::Type::AIR) {

					//check 
					if (j *Chunk::TILESIZE < topRightLocY + m_size.y && (j + 0.5) *Chunk::TILESIZE > topRightLocY + m_size.y
						&& topRightLocX + m_size.x >(i) *Chunk::TILESIZE && topRightLocX < (i + 1) * Chunk::TILESIZE
						&& chunkPtr->GetTileAt(i, j - 1)->type == Chunk::Type::AIR) {

						m_pos.y = j * Chunk::TILESIZE + chunkPtr->GetY()* Chunk::TILESIZE* Chunk::SIZE - m_size.y / 2;
						m_motion.y = 0;

					} else if ((i + 1) * Chunk::TILESIZE > topRightLocX && (i + 0.5) * Chunk::TILESIZE < topRightLocX
						&& (j + 1) * Chunk::TILESIZE > topRightLocY && j * Chunk::TILESIZE < topRightLocY + m_size.y
						&& chunkPtr->GetTileAt(i + 1, j)->type == Chunk::Type::AIR) {

						if (CheckForUpHill(i, j, chunkPtr) == false) {
							m_pos.x = ((i + 1) + chunkPtr->GetX()*Chunk::SIZE)*Chunk::TILESIZE + m_size.x / 2.0;
						} else if (j == blockposY + (int)floor(m_size.y / Chunk::TILESIZE)) {
							m_pos.y = j * Chunk::TILESIZE + chunkPtr->GetY()* Chunk::TILESIZE* Chunk::SIZE - m_size.y / 2;
						}

					} else if (i * Chunk::TILESIZE < topRightLocX + m_size.x && (i + 0.5) * Chunk::TILESIZE > topRightLocX + m_size.x
						&& (j + 1) * Chunk::TILESIZE > topRightLocY && j * Chunk::TILESIZE < topRightLocY + m_size.y
						&& chunkPtr->GetTileAt(i - 1, j)->type == Chunk::Type::AIR) {

						if (CheckForUpHill(i, j, chunkPtr) == false) {
							m_pos.x = (i + chunkPtr->GetX()*Chunk::SIZE)*Chunk::TILESIZE - m_size.x / 2.0;
						} else if (j == blockposY + (int)floor(m_size.y / Chunk::TILESIZE)) {
							m_pos.y = j * Chunk::TILESIZE + chunkPtr->GetY()* Chunk::TILESIZE* Chunk::SIZE - m_size.y / 2;
						}

					} else if ((j + 1) *Chunk::TILESIZE > topRightLocY && (j + 0.5) *Chunk::TILESIZE < topRightLocY
						&& topRightLocX + m_size.x >(i) *Chunk::TILESIZE && topRightLocX < (i + 1) *Chunk::TILESIZE
						&& chunkPtr->GetTileAt(i, j + 1)->type == Chunk::Type::AIR) {

						m_pos.y = (j + 1) * Chunk::TILESIZE + chunkPtr->GetY()* Chunk::TILESIZE* Chunk::SIZE + m_size.y / 2;
						m_motion.y = 0;
					}

				} else {
					m_motion.y += 1 * deltaTime;
				}
			}
		}
	}
}

bool LandNPC::CheckForUpHill(int i, int j, Chunk* chunkPtr) {
	bool check = true;
	for (int k = 1; k < (int)ceil(m_size.y / Chunk::TILESIZE) + 1; k++) {
		if (chunkPtr->GetTileAt(i, j - k)->type != Chunk::Type::AIR) {
			check = false;
		}
	}
	return check;
}
