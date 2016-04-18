#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

class Avatar;
class Background 
{
public:
	enum Types {
		HIGHMOUNTENS,
		LOWMOUNTENS
	};
	
	Background(Types backtype, int y);
	virtual ~Background( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Background( const Background& ) = delete;
	Background& operator=( const Background& ) = delete;

	void Tick(double deltaTime);
	void Paint(Avatar* avatarPtr);
	
private: 

	const int m_FrameTime = 0.1;
	const int m_FrameAll = 3;
	int m_Frame;
	double m_Counter;
	double m_Y;
	Types m_BackType;
};
