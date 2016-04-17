//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Avatar.h"
#include "Chunk.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

NPC::NPC(DOUBLE2 pos, DOUBLE2 size):m_pos(pos),m_size(size) {
}

NPC::~NPC() {}

DOUBLE2 NPC::GetPosition() {
	return m_pos;
}

DOUBLE2 NPC::GetBlockPos() {
	return m_pos / Chunk::TILESIZE;
}

DOUBLE2 NPC::GetChunkPos() {
	return m_pos / (Chunk::SIZE*Chunk::TILESIZE);
}