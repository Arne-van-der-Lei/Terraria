//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Node.h"

//#define GAME_ENGINE (GameEngine::GetSingleton())

Node::Node(DOUBLE2 value): m_Value(value)
{
}

Node::~Node()
{
	delete m_NextPtr;
	m_NextPtr = nullptr;
}

DOUBLE2 Node::GetValue() {
	return m_Value;
}

Node* Node::GetNode() {
	return m_NextPtr;
}

void Node::SetNext(Node* nodePtr) {
	m_NextPtr = nodePtr;
}