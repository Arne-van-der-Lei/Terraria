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

std::string Inventory::ToString() {
	std::string str;
	str += "<contents>\n";

	for (ItemStack* item : m_contents) {
		str += std::string("<item>\n")
			+ "<id>" + std::to_string(item->GetId()) + "</id>\n"
			+ "<amount>" + std::to_string(item->GetAmount()) + "</amount>\n"
			+ "</item>\n";
	}
	str += "<contents>\n";
	return str;
}

void Inventory::LoadFromString(std::string str) {
	int begin = str.find("<contents>");
	int end = str.find("</contents>");
	str = str.substr(begin, end - begin);
	int teller = 0;
	begin = str.find("<item>");
	do {
		std::string data = str.substr(begin, str.find("</item>",begin+1) - begin);
		m_contents.at(teller)->SetId(FILE_MANAGER->GetIntFromString(data, "id"));
		m_contents.at(teller)->SetAmount(FILE_MANAGER->GetIntFromString(data, "amount"));
		teller++;
		begin = str.find("<item>", begin + 1);
	} while (begin != -1);
}