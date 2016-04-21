#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
class ItemStack;
class Inventory {
public:
	Inventory();
	virtual ~Inventory( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Inventory( const Inventory& ) = delete;
	Inventory& operator=( const Inventory& ) = delete;

	virtual void Paint(bool open,int x,int y);
 
	int m_Width;
	int m_Height;
	std::vector<ItemStack*> m_contents;
};
