#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "World.h"

class NPC 
{
public:
	NPC(DOUBLE2 pos, DOUBLE2 size);
	virtual ~NPC( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	NPC( const NPC& ) = delete;
	NPC& operator=( const NPC& ) = delete;

	virtual void Tick(double deltaTime) = 0;
	virtual void Paint() = 0;
	virtual void DoCollision(World* world, double deltaTime) = 0;
	bool ColidesWith(NPC* NPCPtr);
	virtual std::string ToString();

	DOUBLE2 GetPosition();
	DOUBLE2 GetBlockPos();
	DOUBLE2 GetChunkPos();

	DOUBLE2 m_pos;
	DOUBLE2 m_size;
	DOUBLE2 m_motion;
	DOUBLE2 m_Speed;

};
