//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Camera.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::SetViewMatrix(Avatar* avatarPtr)
{
	MATRIX3X2 matView;
	DOUBLE2 pos = avatarPtr->GetPosition();
	pos.x -= GAME_ENGINE->GetWidth() / 2.0;
	pos.y -= GAME_ENGINE->GetHeight() / 2.0;

	pos.x = floor(pos.x);
	pos.y = floor(pos.y);

	matView.SetAsTranslate(-pos);

	GAME_ENGINE->SetViewMatrix(matView);
}