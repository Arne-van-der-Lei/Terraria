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

Avatar::Avatar(DOUBLE2 pos, DOUBLE2 size): LandNPC(pos,size){}

Avatar::~Avatar(){}

void Avatar::Tick(double deltaTime)
{	
	m_motion.x = 0;
	if (m_isOnGround) {
		m_ActionStateBody = ActionState::IDEL;
		m_ActionStateFeet = ActionState::IDEL;
	}

	if (GAME_ENGINE->IsKeyboardKeyDown('Q')) {
		m_motion.x = -120*deltaTime;
		m_Dir = false;
		if (m_ActionStateBody != ActionState::JUMPING && m_ActionStateFeet != ActionState::JUMPING) {
			if (m_ActionStateBody != ActionState::SWINGING) {
				m_ActionStateBody = ActionState::WALKING;
				if (m_FrameBody < 6) {
					m_FrameBody = 6;
				}
			}
			m_ActionStateFeet = ActionState::WALKING;
			if (m_FrameFeet < 6) {
				m_FrameFeet = 6;
			}
		}
	}

	if (GAME_ENGINE->IsKeyboardKeyDown('D')) {
		m_motion.x = 120* deltaTime;
		m_Dir = true;
		if (m_ActionStateBody != ActionState::JUMPING && m_ActionStateFeet != ActionState::JUMPING) {
			if (m_ActionStateBody != ActionState::SWINGING) {
				m_ActionStateBody = ActionState::WALKING;
				if (m_FrameBody < 6) {
					m_FrameBody = 6;
				}
			}
			m_ActionStateFeet = ActionState::WALKING;
			if (m_FrameFeet < 6) {
				m_FrameFeet = 6;
			}
		}
	}

	if (GAME_ENGINE->IsKeyboardKeyPressed(VK_SPACE)) {
		m_motion.y = -600* deltaTime;
		m_ActionStateBody = ActionState::JUMPING;
		m_ActionStateFeet = ActionState::JUMPING;
	}

	if (GAME_ENGINE->IsMouseButtonDown(VK_LBUTTON)) {
		m_ActionStateBody = ActionState::SWINGING;
		
	}
	
	ChangeFrame(deltaTime);
}

void Avatar::Paint()
{
	MATRIX3X2 matWorld, matTrans, matScale, matOffset;

	matTrans.SetAsTranslate(m_pos.x + (m_Dir * 2 - 1) * 8, m_pos.y + 18);
	matScale.SetAsScale((m_Dir * 2 - 1) * 2, 2);
	matOffset.SetAsTranslate(-m_size.x / 2.0, -m_size.y / 2.0);

	matWorld = matOffset * matScale * matTrans;

	RECT2 rect;
	rect.left = 0;
	rect.top = m_FrameBody * m_FrameHeight;
	rect.right = m_FrameWidth;
	rect.bottom = m_FrameBody *m_FrameHeight + m_FrameHeight;

	//GAME_ENGINE->FillRect(m_pos.x - m_size.x / 2.0, m_pos.y - m_size.y / 2.0, m_pos.x + m_size.x / 2.0, m_pos.y + m_size.y / 2.0);
	GAME_ENGINE->SetWorldMatrix(matWorld);
	for (int i = 0; i < m_FramesFeet; i++) {
		Bitmap* bmpPtr = FILE_MANAGER->GetAvatarBitmap(i);
		GAME_ENGINE->DrawBitmap(bmpPtr,rect);
	}

	rect.left = 0;
	rect.top = m_FrameFeet * m_FrameHeight;
	rect.right = m_FrameWidth;
	rect.bottom = m_FrameFeet *m_FrameHeight + m_FrameHeight;

	for (int i = m_FramesFeet; i < m_FrameAll; i++) {
		Bitmap* bmpPtr = FILE_MANAGER->GetAvatarBitmap(i);
		GAME_ENGINE->DrawBitmap(bmpPtr, rect);
	}
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

void Avatar::ChangeFrame(double deltaTime) {

	m_Counter += deltaTime;

	if (m_Counter > m_FrameTime) {
		switch (m_ActionStateBody) {
		case ActionState::IDEL :
			m_FrameBody = m_FrameIdelStart;
			break;
		case ActionState::JUMPING:
			m_FrameBody = m_FrameJumpingStart;
			break;
		case ActionState::SWINGING:
			m_FrameBody++;
			m_FrameBody %= m_FrameSwingingEnd;
			if (m_FrameBody == 0) {
				m_FrameBody = m_FrameSwingingStart;
			}
			break;
		case ActionState::WALKING:
			m_FrameBody++;
			m_FrameBody %= m_FrameWalkingEnd;
			if (m_FrameBody == 0) {
				m_FrameBody = m_FrameWalkingStart;
			}
			break;
		}

		switch (m_ActionStateFeet) {
		case ActionState::IDEL:
			m_FrameFeet = m_FrameIdelStart;
			break;
		case ActionState::JUMPING:
			m_FrameFeet = m_FrameJumpingStart;
			break;
		case ActionState::WALKING:
			m_FrameFeet++;
			m_FrameFeet %= m_FrameWalkingEnd;
			if (m_FrameFeet == 0) {
				m_FrameFeet = m_FrameWalkingStart;
			}
			break;
		}
		m_Counter -= m_FrameTime;
	}
}