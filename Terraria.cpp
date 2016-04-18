//-----------------------------------------------------------------
// Game Engine Object
// C++ Source - Terraria.cpp - version v2_18 feb 2016 
// Copyright Kevin Hoefman, 2006 - 2011 
// Copyright DAE Programming Team, 2012 - 2016 
// http://www.digitalartsandentertainment.be/ 
//-----------------------------------------------------------------

// this include must be the first include line of every cpp file (due to using precompiled header)
#include "stdafx.h"		

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Terraria.h"																				
#include "Avatar.h"
#include "Camera.h"
#include "World.h"
#include "Filemanager.h"
#include "Chunk.h"
#include "Zombie.h"
//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

//-----------------------------------------------------------------
// Terraria methods																				
//-----------------------------------------------------------------

Terraria::Terraria()
{
	// nothing to create
}

Terraria::~Terraria()
{
	// nothing to destroy
}

void Terraria::GameInitialize(GameSettings &gameSettingsRef)
{
	gameSettingsRef.SetWindowTitle(String("Terraria - van der Lei, Arne - DAE16"));
	gameSettingsRef.SetWindowWidth(1920);
	gameSettingsRef.SetWindowHeight(1080);
	gameSettingsRef.EnableConsole(true);
	gameSettingsRef.EnableAntiAliasing(false);
}

void Terraria::GameStart()
{
	GAME_ENGINE->SetBitmapInterpolationModeNearestNeighbor();
	m_AvatarPtr = new Avatar({ 16 * 32 * 10,16 * 32 * 2 }, { 48,84 });
	m_CameraPtr = new Camera();
	m_WorldPtr = new World();
	m_NPCArrPtr.push_back(new Zombie({ 9 * 32 * 16,0 }, {58,90}));
}

void Terraria::GameEnd()
{
	FileManager::GetSingleton()->RemoveAllTextures();

	delete m_AvatarPtr;
	m_AvatarPtr = nullptr;

	delete m_CameraPtr;
	m_CameraPtr = nullptr;

	delete m_WorldPtr;
	m_WorldPtr = nullptr;

	for (NPC* NPCPtr : m_NPCArrPtr) {
		delete NPCPtr;
		NPCPtr = nullptr;
	}
}

void Terraria::GameTick(double deltaTime)
{
	m_deltatime = deltaTime;

	if (GAME_ENGINE->IsMouseButtonPressed(VK_LBUTTON)) {
		DOUBLE2 mousePos = GAME_ENGINE->GetMousePosition();

		DOUBLE2 worldMousePos = m_CameraPtr->GetViewMatrix(m_AvatarPtr).Inverse().TransformPoint(mousePos);

		DOUBLE2 chunkPos = worldMousePos / (Chunk::TILESIZE*Chunk::SIZE);
		m_WorldPtr->GetChunkAt(chunkPos)->DigTileAt(worldMousePos.x / Chunk::TILESIZE - (int)chunkPos.x * Chunk::SIZE  , worldMousePos.y / Chunk::TILESIZE - (int)chunkPos.y * Chunk::SIZE);
	}

	m_AvatarPtr->Tick(deltaTime);
	m_AvatarPtr->DoCollision(m_WorldPtr, deltaTime);
	for (NPC* NPCPtr : m_NPCArrPtr) {
		if (dynamic_cast<Hostile *>(NPCPtr)) {
			dynamic_cast<Hostile *>(NPCPtr)->Tick(deltaTime, m_AvatarPtr);
		}
		NPCPtr->DoCollision(m_WorldPtr,deltaTime);
	}
	
	m_WorldPtr->Tick(deltaTime,m_AvatarPtr);
}

void Terraria::GamePaint()
{

	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());

	Bitmap * bitmapPtr = FILE_MANAGER->GetBackgroundBitmap(0);
	for (int i = 0; i <= 40; i++) {
		GAME_ENGINE->DrawBitmap(bitmapPtr, i*bitmapPtr->GetWidth(), 0);
	}
	m_WorldPtr->PaintBackground(m_AvatarPtr);

	GAME_ENGINE->SetViewMatrix(m_CameraPtr->GetViewMatrix(m_AvatarPtr));

	m_WorldPtr->Paint(m_AvatarPtr->GetChunkPos().x, m_AvatarPtr->GetChunkPos().y);
	m_AvatarPtr->Paint();

	for (NPC* NPCPtr : m_NPCArrPtr) {
		NPCPtr->Paint();
	}

	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());
	GAME_ENGINE->DrawString(String(floor(m_AvatarPtr->GetPosition().x / (double)(Chunk::TILESIZE*Chunk::SIZE))), 0, 0);
	GAME_ENGINE->DrawString(String(floor(m_AvatarPtr->GetPosition().y / (double)(Chunk::TILESIZE*Chunk::SIZE))), 0, 12);
	GAME_ENGINE->DrawString(String(m_AvatarPtr->GetBlockPos().x), 0, 24);
	GAME_ENGINE->DrawString(String(m_AvatarPtr->GetBlockPos().y), 0, 36);
	GAME_ENGINE->DrawString(String(1/m_deltatime), 0, 48);
}
