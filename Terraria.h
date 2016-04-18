//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - Terraria.h - version v2_18 feb 2016 
// Copyright Kevin Hoefman, 2006 - 2011 
// Copyright DAE Programming Team, 2012 - 2016 
// http://www.digitalartsandentertainment.be/ 
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Student data
// Name: arne van der Lei
// Group: DAE 16
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "AbstractGame.h"
#include "Filemanager.h"

class Avatar;
class Camera;
class World;
class NPC;

//-----------------------------------------------------------------
// Terraria Class																
//-----------------------------------------------------------------
class Terraria : public AbstractGame
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Terraria();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Terraria();

	// C++11 make the class non-copyable
	Terraria(const Terraria&) = delete;
	Terraria& operator=(const Terraria&) = delete;

	//---------------------------
	// General Methods
	//---------------------------

	virtual void GameInitialize(GameSettings &gameSettingsRef);
	virtual void GameStart();
	virtual void GameEnd();
	virtual void GameTick(double deltaTime);
	virtual void GamePaint();

	// -------------------------
	// Public Member functions
	// -------------------------
private:
	// -------------------------
	// Private Member functions
	// -------------------------

	// -------------------------
	// Private Datamembers
	// -------------------------

	Avatar* m_AvatarPtr = nullptr;
	Camera* m_CameraPtr = nullptr;
	bool m_PHDR = false;
	World* m_WorldPtr = nullptr;

	std::vector<NPC* > m_NPCArrPtr; 

	double m_deltatime = 0;
};

