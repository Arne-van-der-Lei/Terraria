//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "AvatarInv.h"
#include "Filemanager.h"
#include "ItemStack.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

AvatarInv::AvatarInv(){
	for (int i = 0; i < m_Width; i++) {
		m_hotbar.push_back(new ItemStack(0, 0));
	}
}

AvatarInv::~AvatarInv(){
	Inventory::~Inventory();
	for (ItemStack* item : m_hotbar) {
		delete item;
		item = nullptr;
	}
}

void AvatarInv::Paint(bool open,int x,int y) {
	if (open) {
		Inventory::Paint(open,x,50+5+y);
	}
	for (int j = 0; j < m_Width; j++) {
		GAME_ENGINE->DrawBitmap(FILE_MANAGER->GetHUDBitmap(0), j * 55 + x, y);
		if (m_hotbar.at(j)->GetAmount() != 0) {
			m_hotbar.at(j)->Paint(x, j*55 + y);
		}
	}
}