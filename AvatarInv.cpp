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

AvatarInv::AvatarInv():Inventory(){
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
		if(m_selected == j){
			GAME_ENGINE->DrawBitmap(FILE_MANAGER->GetHUDBitmap(14), j * 55 + x, y);
		} else {
			GAME_ENGINE->DrawBitmap(FILE_MANAGER->GetHUDBitmap(0), j * 55 + x, y);
		}
		FILE_MANAGER->DrawString(String(String(j+1).At(String(j+1).Length()-1)), { (double)j * 55 + x + 6, (double)y -10 });
		if (m_hotbar.at(j)->GetAmount() != 0) {
			m_hotbar.at(j)->Paint( j * 55 + x, y);
		}
	}
}

bool AvatarInv::AddItemToInventory(ItemStack* itemStackPtr) {
	for (ItemStack* item : m_hotbar) {
		if (item->Add(itemStackPtr)) {
			return true;
		}
	}

	return Inventory::AddItemToInventory(itemStackPtr);
}

ItemStack* AvatarInv::GetSelectedItem() {
	return m_hotbar.at(m_selected);
}

void AvatarInv::SetSelected(int value) {
	m_selected = value;
}