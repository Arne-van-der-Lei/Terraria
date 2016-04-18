#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

class Animatable {
public:
	Animatable();
	virtual ~Animatable( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Animatable( const Animatable& ) = delete;
	Animatable& operator=( const Animatable& ) = delete;


	virtual void updateFrame(double deltaTime);
	DOUBLE2 m_FrameSize;
	double m_FrameTime;
	int m_MaxFrames;
	int m_Frame;
private: 
	double m_Counter = 0;

};
