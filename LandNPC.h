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

	virtual void Tick(double deltaTime) {};
	virtual void Paint() {};
	virtual void DoCollision(World* world, double deltaTime);
	virtual bool afterMathUpHill(int x, int y, Chunk* chunkPtr, bool result) { return result; };
	virtual int GetHealth();
	virtual int GetMaxHealth();
	virtual std::string ToString();
protected:
	bool CheckForUpHill(int x, int y, Chunk* chunkPtr);
	bool m_isOnGround;

	int m_Health;
	int m_MaxHealth;
};
