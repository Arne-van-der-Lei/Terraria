#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

#include "LandNPC.h"
#include "Hostile.h"
#include "Animatable.h"

class Zombie : public LandNPC, public Hostile,public Animatable
{
public:
	Zombie(DOUBLE2 pos, DOUBLE2 size);
	virtual ~Zombie( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Zombie( const Zombie& ) = delete;
	Zombie& operator=( const Zombie& ) = delete;

	virtual void Tick(double deltaTime,Avatar* avatar);
	virtual void Paint();
private: 

	bool m_Dir;
};
