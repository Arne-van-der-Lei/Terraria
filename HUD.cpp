//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "HUD.h"
#include "AvatarInv.h"

HUD::HUD(){
	m_CurrentInvPtr = new AvatarInv();
	m_Open = false;
}

HUD::~HUD(){
	delete m_CurrentInvPtr;
	m_CurrentInvPtr = nullptr;
}

void HUD::Paint() {
	if (m_CurrentChestPtr != nullptr) {
		m_CurrentChestPtr->Paint(m_Open, 50, 50 + 4 * 50 + 4 * 5);
	}

	if (m_CurrentInvPtr != nullptr) {
		m_CurrentInvPtr->Paint(m_Open, 50, 50);
	}
}

void HUD::ToggleInventory() {
	m_Open = !m_Open;
}