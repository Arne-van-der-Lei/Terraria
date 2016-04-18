//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Zombie.h"
#include "Filemanager.h"
#include "Avatar.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

Zombie::Zombie(DOUBLE2 pos,DOUBLE2 size):LandNPC(pos,size){
	m_Speed.x = 120;

	m_FrameSize = DOUBLE2( 34,48 );
	m_FrameTime = 0.2;
	m_MaxFrames = 3;
}

Zombie::~Zombie(){}

void Zombie::Tick(double deltaTime,Avatar* avatarPtr)
{
	if (avatarPtr->GetPosition().x > m_pos.x) {
		m_motion.x = m_Speed.x*deltaTime;
		m_Dir = false;
	}
	if (avatarPtr->GetPosition().x < m_pos.x) {
		m_motion.x = -m_Speed.x*deltaTime;
		m_Dir = true;
	}

	updateFrame(deltaTime);
}

void Zombie::Paint()
{
	MATRIX3X2 matWorld, matTrans, matScale, matOffset;
	matTrans.SetAsTranslate(m_pos.x, m_pos.y );
	matScale.SetAsScale((m_Dir * 2 - 1)*2,2);
	matOffset.SetAsTranslate(-m_FrameSize.x / 2.0, -m_FrameSize.y / 2.0);

	matWorld = matOffset * matScale * matTrans;

	RECT2 rect;
	rect.left = 0;
	rect.top = m_Frame * m_FrameSize.y;
	rect.right = m_FrameSize.x;
	rect.bottom = m_Frame * m_FrameSize.y + m_FrameSize.y;
	//GAME_ENGINE->FillRect(m_pos.x - m_size.x / 2.0, m_pos.y - m_size.y / 2.0, m_pos.x + m_size.x / 2.0, m_pos.y + m_size.y / 2.0);
	GAME_ENGINE->SetWorldMatrix(matWorld);
	GAME_ENGINE->DrawBitmap(FILE_MANAGER->GetNPCBitmap(2),rect);
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}