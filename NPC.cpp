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

bool NPC::ColidesWith(NPC* NPCPtr) {
	if (m_pos.x < NPCPtr->m_pos.x + NPCPtr->m_size.x && m_pos.x + m_size.x > NPCPtr->m_pos.x &&
		m_pos.y < NPCPtr->m_pos.y + NPCPtr->m_size.y && m_pos.y + m_size.y > NPCPtr->m_pos.y) {
		//std::cout << "hello" << std::endl;
		return true;
	}
	return false;
}

std::string NPC::ToString() {
	return "<motion>" + std::string(m_motion.ToString().C_str()) + "</motion>\n"
		+ "<pos>" + std::string(m_pos.ToString().C_str()) + "</pos>\n"
		+ "<size>" + std::string(m_pos.ToString().C_str()) + "<size>\n"
		+ "<speed>" + std::string(m_pos.ToString().C_str()) + "<speed>\n";
}