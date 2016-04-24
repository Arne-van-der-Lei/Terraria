//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "HUD.h"
#include "AvatarInv.h"
#include "ItemStack.h"
#include "Avatar.h"
#include "Filemanager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

HUD::HUD(){
	m_CurrentInvPtr = new AvatarInv();
	m_Open = false;

	m_CurrentInvPtr->AddItemToInventory(new ItemStack(1,1));
	m_CurrentInvPtr->AddItemToInventory(new ItemStack(3,64));
}

HUD::~HUD(){
	delete m_CurrentInvPtr;
	m_CurrentInvPtr = nullptr;
}

void HUD::Paint(Avatar* avatarPtr) {
	if (m_CurrentChestPtr != nullptr) {
		m_CurrentChestPtr->Paint(m_Open, 50, 50 + 4 * 50 + 4 * 5);
	}

	if (m_CurrentInvPtr != nullptr) {
		m_CurrentInvPtr->Paint(m_Open, 50, 50);
	}


	FILE_MANAGER->DrawString(String("Life: ") + String(avatarPtr->GetHealth()) + String("/") + String(avatarPtr->GetMaxHealth()), { (double)GAME_ENGINE->GetWidth() - 450, (double)20 });
	Bitmap* bitmapPtr = FILE_MANAGER->GetHUDBitmap(16);
	for (int i = 0; i < avatarPtr->GetHealth() / 20; i++) {
		GAME_ENGINE->DrawBitmap(bitmapPtr, GAME_ENGINE->GetWidth() - 400 + i* bitmapPtr->GetWidth() + i*10, 50);
	}

}

void HUD::ToggleInventory() {
	m_Open = !m_Open;
}

void HUD::AddItem(ItemStack* itemPtr) {
	m_CurrentInvPtr->AddItemToInventory(itemPtr);
}

bool HUD::IsOpen() {
	return m_Open;
}

ItemStack* HUD::GetSelectedItem() {
	return dynamic_cast<AvatarInv*>( m_CurrentInvPtr)->GetSelectedItem();
}

void HUD::Tick(double deltaTime) {
	for (int i = 1; i < 11; i++) {
		if (GAME_ENGINE->IsKeyboardKeyPressed((char)(i%10 + 48))) {
			dynamic_cast<AvatarInv*>(m_CurrentInvPtr)->SetSelected(i-1);
		}
	}
}

std::string HUD::ToString() {
	return "<hud>\n";
}