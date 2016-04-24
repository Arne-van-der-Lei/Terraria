#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "Inventory.h"

class ItemStack;

class AvatarInv: public Inventory {
public:
	AvatarInv();
	virtual ~AvatarInv( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	AvatarInv( const AvatarInv& ) = delete;
	AvatarInv& operator=( const AvatarInv& ) = delete;

	virtual void Paint(bool open, int x, int y);
	virtual bool AddItemToInventory(ItemStack* itemStackPtr);
	virtual ItemStack* GetSelectedItem();
	virtual void SetSelected(int value);
	virtual std::string ToString();
	virtual void LoadFromString(std::string str);
private: 

	std::vector<ItemStack*> m_hotbar;
	int m_selected = 0;
};
