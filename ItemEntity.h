#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "World.h"
#include "NPC.h"
#include "Hostile.h"

class ItemEntity : public NPC, public Hostile
{
public:
	ItemEntity(DOUBLE2 pos, DOUBLE2 size, int id);
	virtual ~ItemEntity( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	ItemEntity( const ItemEntity& ) = delete;
	ItemEntity& operator=( const ItemEntity& ) = delete;

	virtual void Tick(double deltaTime) {};
	virtual void Tick(double deltaTime, Avatar* avatar, World* worldPtr);
	virtual void Paint();
	virtual void DoCollision(World* world, double deltaTime);

	int GetId();
protected:
	bool m_isOnGround;

	int m_Id;
};
