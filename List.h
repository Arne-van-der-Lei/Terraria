#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
class Node;
class List 
{
public:
	List( );
	virtual ~List( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	List( const List& ) = delete;
	List& operator=( const List& ) = delete;

	void Add(DOUBLE2 value , DOUBLE2 value2);
	void Remove(DOUBLE2 value);
	std::vector<DOUBLE2> ToVector();
private: 

	Node* m_FirstPtr = nullptr;
};
