#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
class Avatar;

class Hostile {
public:
	Hostile();
	virtual ~Hostile( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Hostile( const Hostile& ) = delete;
	Hostile& operator=( const Hostile& ) = delete;

	virtual void Tick(double deltaTime,Avatar* avatar) = 0;
	virtual void Paint() = 0;
private: 


};
