//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"
#include "Camera.h"
#include "World.h"
#include "Chunk.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Camera::Camera()
{
}

Camera::~Camera()
{
}

MATRIX3X2 Camera::GetViewMatrix(Avatar* avatarPtr)
{
	MATRIX3X2 matView;
	DOUBLE2 pos = avatarPtr->GetPosition();
	pos = ClampToLevel(pos);

	pos.x -= GAME_ENGINE->GetWidth() / 2.0;
	pos.y -= GAME_ENGINE->GetHeight() / 2.0;

	pos.x = floor(pos.x);
	pos.y = floor(pos.y);

	matView.SetAsTranslate(-pos);

	return matView;
}

DOUBLE2 Camera::ClampToLevel(DOUBLE2 pos) {
	if (pos.x < GAME_ENGINE->GetWidth() / 2) {
		pos.x = GAME_ENGINE->GetWidth() / 2;
	}
	if (pos.y < GAME_ENGINE->GetHeight() / 2) {
		pos.y = GAME_ENGINE->GetHeight() / 2;
	}

	if (pos.x > Chunk::TILESIZE * Chunk::SIZE * World::WIDTH - GAME_ENGINE->GetWidth() / 2) {
		pos.x = Chunk::TILESIZE * Chunk::SIZE * World::WIDTH - GAME_ENGINE->GetWidth() / 2;
	}
	if (pos.y > Chunk::TILESIZE * Chunk::SIZE * World::WIDTH - GAME_ENGINE->GetHeight() / 2) {
		pos.y = Chunk::TILESIZE * Chunk::SIZE * World::WIDTH - GAME_ENGINE->GetHeight() / 2;
	}
	return pos;
}