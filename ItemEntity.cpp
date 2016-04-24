//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "ItemEntity.h"
#include "Chunk.h"
#include "Avatar.h"
#include "Filemanager.h"

#define FILE_MANAGER (FileManager::GetSingleton())
#define GAME_ENGINE (GameEngine::GetSingleton())

ItemEntity::ItemEntity(DOUBLE2 pos, DOUBLE2 size,int id): NPC( pos, size),m_Id(id) {
	m_isOnGround = false;

	m_Speed.x = 1000;
	m_Speed.y = 1000;
}

ItemEntity::~ItemEntity() {}

void ItemEntity::Tick(double deltaTime, Avatar* avatar, World* worldPtr) {
	DOUBLE2 avapos = avatar->GetPosition();
	if ((avapos - m_pos).Length() < Chunk::TILESIZE * 5) {
		m_motion.x = (1 / (avatar->GetPosition() - m_pos).x)*deltaTime*m_Speed.x;
		m_motion.y = (1 / (avatar->GetPosition() - m_pos).y)*deltaTime*m_Speed.y;
	}
}

void ItemEntity::Paint() {
	//std::cout << "cookies: " << m_Id << " pos: " << m_pos.x << " , " << m_pos.y << std::endl;
	Bitmap * bitmapPtr = FILE_MANAGER->GetItemBitmap(m_Id);
	MATRIX3X2 matWorld, matTrans, matScale, matOffset;
	matTrans.SetAsTranslate(m_pos.x, m_pos.y);
	matOffset.SetAsTranslate(-bitmapPtr->GetWidth()/2, -bitmapPtr->GetHeight()/2);
	matScale.SetAsScale(2);

	matWorld = matOffset * matScale * matTrans;

	//GAME_ENGINE->FillRect(m_pos.x - m_size.x / 2.0, m_pos.y - m_size.y / 2.0, m_pos.x + m_size.x / 2.0, m_pos.y + m_size.y / 2.0);
	GAME_ENGINE->SetWorldMatrix(matWorld);
	GAME_ENGINE->DrawBitmap(bitmapPtr);
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

void ItemEntity::DoCollision(World* world, double deltaTime) {
	m_pos.x += m_motion.x;
	m_pos.y += m_motion.y;

	int toprightX = (int)(m_pos.x - m_size.x / 2.0);
	int toprightY = (int)(m_pos.y - m_size.y / 2.0);

	Chunk* chunkPtr = world->GetChunkAt(toprightX / (Chunk::TILESIZE*Chunk::SIZE), toprightY / (Chunk::TILESIZE*Chunk::SIZE));

	if (chunkPtr == nullptr) {
		m_motion.y += 1 * deltaTime;
		return;
	}

	int blockposX = toprightX / (Chunk::TILESIZE) - chunkPtr->GetX()*Chunk::SIZE;
	int blockposY = (toprightY + m_size.y/2.0) / (Chunk::TILESIZE) - chunkPtr->GetY()*Chunk::SIZE;

	Tile* tilePtr = chunkPtr->GetTileAt(blockposX, blockposY);
	double topRightLocX = toprightX - chunkPtr->GetX()* Chunk::TILESIZE* Chunk::SIZE;
	double topRightLocY = toprightY - chunkPtr->GetY()* Chunk::TILESIZE* Chunk::SIZE;

	if (tilePtr != nullptr) {
		if (tilePtr->type != Chunk::Type::AIR) {
			m_pos.y = blockposY * Chunk::TILESIZE + chunkPtr->GetY()* Chunk::TILESIZE* Chunk::SIZE - m_size.y / 2;
			m_motion.y = 0;
		} else {
			m_motion.y += 1 * deltaTime;
		}
	}
}

int ItemEntity::GetId() {
	return m_Id;
}