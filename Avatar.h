#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "World.h"
#include "LandNPC.h"

class Avatar : public LandNPC
{
public:
	Avatar( );
	virtual ~Avatar( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Avatar( const Avatar& ) = delete;
	Avatar& operator=( const Avatar& ) = delete;

	virtual void Tick(double deltaTime);
	virtual void Paint();
private: 
};
