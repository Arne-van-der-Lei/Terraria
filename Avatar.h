#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "World.h"

class Avatar 
{
public:
	Avatar( );
	virtual ~Avatar( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Avatar( const Avatar& ) = delete;
	Avatar& operator=( const Avatar& ) = delete;

	void Tick(double deltaTime);
	void Paint();
	void DoCollision(World* world,double deltaTime);
	DOUBLE2 GetPosition();
	DOUBLE2 GetBlockPos();
	DOUBLE2 GetChunkPos();
private: 

	bool CheckForUpHill(int i , int j , Chunk* chunkPtr);
	DOUBLE2 m_pos;
	DOUBLE2 m_size;
	DOUBLE2 m_motion;

	DOUBLE2 m_blockPos;

	bool m_isOnGround;
};
