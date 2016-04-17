//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Avatar.h"
#include "Chunk.h"
#include "Filemanager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

Avatar::Avatar() : LandNPC({ 16 * 32 * 10,16 * 32 * 2 }, {40,90})
{

}

Avatar::~Avatar()
{
}

void Avatar::Tick(double deltaTime)
{	
	m_motion.x = 0;

	if (GAME_ENGINE->IsKeyboardKeyDown('Q')) {
		m_motion.x = -120*deltaTime;
	}

	if (GAME_ENGINE->IsKeyboardKeyDown('D')) {
		m_motion.x = 120* deltaTime;
	}

	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_SPACE)) {
		m_motion.y = -600* deltaTime;
	}

	m_pos.x += m_motion.x;
	m_pos.y += m_motion.y;
}

void Avatar::Paint()
{
	GAME_ENGINE->SetColor(COLOR(0, 0, 0));
	GAME_ENGINE->FillRect(m_pos.x - m_size.x / 2.0, m_pos.y - m_size.y / 2.0, m_pos.x + m_size.x / 2.0, m_pos.y + m_size.y / 2.0);

	MATRIX3X2 matWorld, matTrans, matScale;

	matTrans.SetAsTranslate(m_pos.x- m_size.x / 2.0, m_pos.y - m_size.y / 2.0);
	matScale.SetAsScale(2);

	matWorld = matScale*matTrans;

	GAME_ENGINE->SetWorldMatrix(matWorld);
	for (int i = 0; i < 14; i++) {

		Bitmap* bmpPtr = FILE_MANAGER->GetBackgroun;
		GAME_ENGINE->DrawBitmap(bmpPtr);
	}
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}