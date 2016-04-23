//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "ItemStack.h"
#include "Filemanager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

ItemStack::ItemStack(int id):m_id(id),m_Amount(1){
	
}

ItemStack::ItemStack(int id, int amount) : m_id(id),m_Amount(amount){

}

ItemStack::~ItemStack(){
}

void ItemStack::Paint(int x,int y) {
	GAME_ENGINE->DrawBitmap(FILE_MANAGER->GetItemBitmap(m_id),x+10,y+10);
	FILE_MANAGER->DrawString(String(m_Amount), { (double)x, (double)y });
}

bool ItemStack::Add(ItemStack* itemStack) {
	if (itemStack->GetId() == m_id || m_id == 0) {
		m_id = itemStack->GetId();
		if (m_Amount + itemStack->GetAmount() >= MAXSTACKSIZE ) {
			m_Amount = MAXSTACKSIZE - 1;
			itemStack->SetAmount(m_Amount + itemStack->GetAmount() - (MAXSTACKSIZE-1));
		} else {
			m_Amount += itemStack->GetAmount();
			itemStack->SetAmount(0);
		}
		return true;
	}
	return false;
}

int ItemStack::GetAmount() {
	return m_Amount;
}

int ItemStack::GetId() {
	return m_id;
}

void ItemStack::SetAmount(int amount) {
	m_Amount = amount;
}