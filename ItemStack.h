#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
class Avatar;
class World;
class ItemStack {
public:
	ItemStack(int id); 
	ItemStack(int id,int amount);
	virtual ~ItemStack( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	ItemStack( const ItemStack& ) = delete;
	ItemStack& operator=( const ItemStack& ) = delete;

	virtual void Paint(int x,int y);

	bool Add(ItemStack* itemStack);
	bool Devide(ItemStack* itemStack);
	void SetAmount(int amount);
	int GetAmount();
	int GetId();
private: 
	int m_id;
	int m_Amount;
	const int MAXSTACKSIZE = 1000;
};
