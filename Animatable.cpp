//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Animatable.h"

Animatable::Animatable(){}

Animatable::~Animatable(){}


void Animatable::updateFrame(double deltaTime) {
	m_Counter += deltaTime;

	if (m_Counter > m_FrameTime) {
		m_Frame++;
		m_Frame %= m_MaxFrames;
		m_Counter -= m_FrameTime;
	}
}