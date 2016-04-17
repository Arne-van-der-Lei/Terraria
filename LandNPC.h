#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "World.h"
#include "NPC.h"

class LandNPC : public NPC
{
public:
	LandNPC(DOUBLE2 pos, DOUBLE2 size);
	virtual ~LandNPC( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	LandNPC( const LandNPC& ) = delete;
	LandNPC& operator=( const LandNPC& ) = delete;

	virtual void Tick(double deltaTime) ;
	virtual void Paint();
	virtual void DoCollision(World* world, double deltaTime);
protected:
	bool CheckForUpHill(int i, int j, Chunk* chunkPtr);
	bool m_isOnGround;
};
