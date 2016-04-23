//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Inventory.h"
#include "Filemanager.h"
#include "ItemStack.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

Inventory::Inventory():m_Width(10),m_Height(4){
	for (int i = 0; i < m_Height; i++) {
		for (int j = 0; j < m_Width; j++) {
			m_contents.push_back(new ItemStack(0, 0));
		}
	}
}

Inventory::~Inventory(){
	for (ItemStack* item : m_contents) {
		delete item;
		item = nullptr;
	}
}

void Inventory::Paint(bool open, int x,int y) {
	//std::cout << open << std::endl;
	for (int i = 0; i < m_Height;i++) {
		for (int j = 0; j < m_Width; j++) {
			GAME_ENGINE->DrawBitmap(FILE_MANAGER->GetHUDBitmap(0), j * 55 + x, y + i * 55);
			if (m_contents.at(i*m_Height + j)->GetAmount() != 0) {
				m_contents.at(i*m_Height + j)->Paint(i*55+x, j*55+y);
			}
		}
	}
}


bool Inventory::AddItemToInventory(ItemStack* itemStackPtr) {
	for (ItemStack* item : m_contents) {
		if (item->Add(itemStackPtr)) {
			return true;
		}
	}
	return false;
}