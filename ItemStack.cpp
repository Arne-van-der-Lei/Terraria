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
	Bitmap * bitmapPtr = FILE_MANAGER->GetItemBitmap(m_id);
	GAME_ENGINE->DrawBitmap(bitmapPtr,x + 25 - bitmapPtr->GetWidth()/2 ,y + 25 - bitmapPtr->GetHeight() / 2 );
	if (m_Amount > 1) {
		FILE_MANAGER->DrawString(String(m_Amount), { (double)x + 10, (double)y + 20 });
	}
}

bool ItemStack::Add(ItemStack* itemStack) {
	if (itemStack->GetId() == m_id || m_id == 0 && m_Amount < MAXSTACKSIZE-1) {
		m_id = itemStack->GetId();
		if (m_Amount + itemStack->GetAmount() >= MAXSTACKSIZE ) {
			m_Amount = MAXSTACKSIZE - 1;
			itemStack->SetAmount(m_Amount + itemStack->GetAmount() - (MAXSTACKSIZE-1));
		} else {
			m_Amount += itemStack->GetAmount();
			itemStack->SetAmount(0);
			return true;
		}
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

void ItemStack::SetId(int id) {
	m_id = id;
}

int ItemStack::GetPlaceId() {
	return m_id - 1;
}
