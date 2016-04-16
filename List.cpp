//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "List.h"
#include "Node.h"

//#define GAME_ENGINE (GameEngine::GetSingleton())

List::List()
{
}

List::~List()
{
	delete m_FirstPtr;
	m_FirstPtr = nullptr;
}

void List::Add(DOUBLE2 value, DOUBLE2 value2)
{
	//not avilable yet
	Node* nodePtr = new Node(value);
	Node* nodePtr2 = new Node(value2);
	if (m_FirstPtr == nullptr) {
		m_FirstPtr = nodePtr;
		return;
	}

	//insert in begin
	if (m_FirstPtr->GetValue() == value2) {
		nodePtr->SetNext(m_FirstPtr);
		m_FirstPtr = nodePtr ;
		return;
	}

	//insert somewhere
	Node* prevNode = m_FirstPtr;
	for (Node* currentNodePtr = m_FirstPtr->GetNode(); currentNodePtr != nullptr; currentNodePtr = currentNodePtr->GetNode()) {
		if (value == currentNodePtr->GetValue()) {
			nodePtr2->SetNext(currentNodePtr->GetNode());
			currentNodePtr->SetNext(nodePtr2);
			return;
		}

		if (value2 == currentNodePtr->GetValue()) {
			prevNode->SetNext(nodePtr);
			nodePtr->SetNext(currentNodePtr);
			return;
		}
		prevNode = currentNodePtr;
		
	}

	//insert end
	prevNode->SetNext(nodePtr2);

}

std::vector<DOUBLE2> List::ToVector() {
	std::vector<DOUBLE2> vec;
	for (Node* currentNodePtr = m_FirstPtr; currentNodePtr != nullptr; currentNodePtr = currentNodePtr->GetNode()) {
		vec.push_back(currentNodePtr->GetValue());
	}
	return vec;
}