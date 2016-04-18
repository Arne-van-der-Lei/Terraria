//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Background.h"
#include "Avatar.h"
#include "Filemanager.h"
#include "World.h"
#include "Chunk.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

Background::Background(Types backtype, int y):m_BackType(backtype),m_Y(y),m_Frame(0),m_Counter(0)
{
}

Background::~Background()
{
}

void Background::Tick(double deltaTime)
{
	m_Counter += deltaTime;
	if (m_Counter > m_FrameTime) {
		m_Frame ++;
		m_Frame %= m_FrameAll;
		m_Counter -= m_FrameTime;
	}
}

void Background::Paint(Avatar* avatarPtr)
{
	Bitmap* bmpBG1Ptr = FILE_MANAGER->GetBackgroundBitmap(1+m_BackType*3 + m_Frame);

	MATRIX3X2 matWorld, matTrans, matScale;

	DOUBLE2 pos = avatarPtr->GetPosition();
	matTrans.SetAsTranslate(-(pos.x / (World::WIDTH * Chunk::TILESIZE * Chunk::SIZE))*bmpBG1Ptr->GetWidth()*2, (-pos.y / (World::HEIGHT*Chunk::TILESIZE * Chunk::SIZE)) * bmpBG1Ptr->GetHeight()*2 + m_Y);
	matScale.SetAsScale(2);

	matWorld = matScale*matTrans;

	GAME_ENGINE->SetWorldMatrix(matWorld);
	GAME_ENGINE->DrawBitmap(bmpBG1Ptr);
	GAME_ENGINE->DrawBitmap(bmpBG1Ptr,bmpBG1Ptr->GetWidth(),0);
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

