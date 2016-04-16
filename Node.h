#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

class Node 
{
public:
	Node(DOUBLE2 value);
	virtual ~Node( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Node( const Node& ) = delete;
	Node& operator=( const Node& ) = delete;

	DOUBLE2 GetValue();
	Node* GetNode();
	void SetNext(Node* nodePtr);

private: 

	DOUBLE2 m_Value;
	Node* m_NextPtr = nullptr;
};
