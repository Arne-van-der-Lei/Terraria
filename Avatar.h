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
	enum class ActionState {
		IDEL,
		WALKING,
		SWINGING,
		JUMPING
	};

	void ChangeFrame(double deltaTime);

	int m_Dir = 1;
	int m_FrameBody = 0;
	int m_FrameFeet = 0;

	const int m_FrameHeight = 56;
	const int m_FrameWidth = 40;

	const int m_FrameIdelStart = 0;

	const int m_FrameSwingingEnd = 5;
	const int m_FrameSwingingStart = 1;

	const int m_FrameWalkingEnd = 20;
	const int m_FrameWalkingStart = 6;

	const int m_FrameJumpingStart = 5;

	const int m_startChunkX = 10;
	const int m_startChunkY = 2;

	const int m_FrameTime = 0.05;

	const int m_sizeX = 48;
	const int m_sizeY = 84;

	const int m_FramesFeet = 10;
	const int m_FrameAll = 14;

	double m_Counter = 0;
	ActionState m_ActionStateBody;
	ActionState m_ActionStateFeet;
};
