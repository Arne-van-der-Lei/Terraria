//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Chunk.h"
#include "World.h"
#include "Terraria.h"
#include "Filemanager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())
#define FILE_MANAGER (FileManager::GetSingleton())

Chunk::Chunk(int x, int y, World * worldPtr) : m_X(x), m_Y(y), m_WorldPtr(worldPtr)
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Tile* tilePtr = new Tile();
			tilePtr->x = i;
			tilePtr->y = j;
			tilePtr->backTileType = BackgroundType::BDIRT;
			tilePtr->type = Type::AIR;
			m_TileArrPtr.push_back(tilePtr);
		}
	}
}

Chunk::~Chunk()
{
	for (size_t i = 0; i < m_TileArrPtr.size(); i++) {
		delete m_TileArrPtr[i];
		m_TileArrPtr[i] = nullptr;
	}
}

void Chunk::AfterInit() {
	for (Tile* tilePtr : m_TileArrPtr) {
		CheckSurroundings(tilePtr);
	}
}

void Chunk::Tick(double deltaTime)
{
	/*for (Tile* tilePtr : m_TileArrPtr) {
		//tilePtr->Tick(deltaTime);
	}*/
}

void Chunk::Paint()
{
	for (Tile* tilePtr : m_TileArrPtr) {
		PaintTileAt(tilePtr);
	}

	GAME_ENGINE->DrawRect(m_X*SIZE*TILESIZE, m_Y*SIZE*TILESIZE, m_X*SIZE*TILESIZE + TILESIZE*SIZE, m_Y*SIZE*TILESIZE + TILESIZE*SIZE);
}

void Chunk::PaintBackground() {
	for (Tile* tilePtr : m_TileArrPtr) {
		PaintBackgroundAt(tilePtr);
	}
}

Tile* Chunk::GetTileAt(int x,int y) {

	if (x >= SIZE) {
		Chunk* current = m_WorldPtr->GetChunkAt(m_X+1, m_Y);
		if (current == nullptr) 
			return nullptr;
		return current->GetTileAt(x-SIZE, y);
	}

	if (x < 0) {
		Chunk* current = m_WorldPtr->GetChunkAt(m_X-1, m_Y);
		if (current == nullptr) 
			return nullptr;
		return current->GetTileAt(x+ SIZE, y );
	}

	if (y >= SIZE) {
		Chunk* current = m_WorldPtr->GetChunkAt(m_X, m_Y + 1);
		if (current == nullptr) 
			return nullptr;
		return current->GetTileAt(x, y - SIZE);
	}

	if(y < 0) {
		Chunk* current = m_WorldPtr->GetChunkAt(m_X, m_Y - 1);
		if (current == nullptr) 
			return nullptr;
		return current->GetTileAt(x, y + SIZE);
	}

	return m_TileArrPtr[x*SIZE + y];
}

void Chunk::DigTileAt(int x,int y) {
	RemoveTileAt(x, y);
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			Tile* tilePtr = GetTileAt(i, j);
			CheckSurroundings(tilePtr);
		}
	}
}

void Chunk::PaintTileAt(Tile* tilePtr) {

	if (tilePtr->type == AIR) return;

	Bitmap* bitmapPtr = FILE_MANAGER->GetBitmap(tilePtr->type);

	MATRIX3X2 matWorld, matTrans, matScale;

	matTrans.SetAsTranslate(tilePtr->x * TILESIZE + m_X*SIZE*TILESIZE, tilePtr->y * TILESIZE + m_Y*SIZE*TILESIZE);
	matScale.SetAsScale(2);

	matWorld = matScale *matTrans;

	RECT2 rect;
	rect.left = tilePtr->air * TILESIZE / 2;
	rect.top = TILESIZE / 2;
	rect.right = tilePtr->air * TILESIZE / 2 + TILESIZE / 2;
	rect.bottom = TILESIZE / 2 + TILESIZE / 2;

	GAME_ENGINE->SetWorldMatrix(matWorld);
	GAME_ENGINE->DrawBitmap(bitmapPtr, rect);
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

void Chunk::PaintBackgroundAt(Tile* tilePtr) {
	if (tilePtr->backTileType == BackgroundType::BAIR) return;
	Bitmap* bitmapWallPtr = FILE_MANAGER->GetWallBitmap(tilePtr->backTileType);

	MATRIX3X2 matTrans, matScale, matWorldWall, matOffset;

	matTrans.SetAsTranslate(tilePtr->x * TILESIZE + m_X*SIZE*TILESIZE, tilePtr->y * TILESIZE + m_Y*SIZE*TILESIZE);
	matOffset.SetAsTranslate(-TILESIZE / 2, -TILESIZE / 2);
	matScale.SetAsScale(2);

	matWorldWall = matScale *matTrans*matOffset;

	RECT2 rectWall;
	rectWall.left = tilePtr->noBackround * TILESIZE;
	rectWall.top = TILESIZE;
	rectWall.right = tilePtr->noBackround * TILESIZE + TILESIZE;
	rectWall.bottom = TILESIZE + TILESIZE;

	GAME_ENGINE->SetWorldMatrix(matWorldWall);
	GAME_ENGINE->DrawBitmap(bitmapWallPtr, rectWall);
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

bool Chunk::CheckTileToAir(Tile* currentTilePtr, Tile* tilePtr) {
	if (tilePtr != nullptr) {
		if (tilePtr->type != Type::AIR) {
			return true;
		}
	}
	return false;
}

bool Chunk::CheckTileToBackgroundAir(Tile* currentTilePtr,Tile* tilePtr) {
	if (tilePtr != nullptr) {
		if (tilePtr->backTileType != BackgroundType::BAIR) {
			return true;
		}
	}
	return false;
}

int Chunk::BoolToInt(bool left, bool right, bool top, bool bottom) {
	int c = 0;
	if (left)
		c |= 1 << 0;
	if (right)
		c |= 1 << 1;
	if (top)
		c |= 1 << 2;
	if (bottom)
		c |= 1 << 3;
	return c;
}

void Chunk::CheckSurroundings(Tile* currentTilePtr) {
	if (currentTilePtr == nullptr) return;
	bool left, right, top, bottom;

	left = CheckTileToAir(currentTilePtr,GetTileAt(currentTilePtr->x - 1, currentTilePtr->y));
	right = CheckTileToAir(currentTilePtr,GetTileAt(currentTilePtr->x + 1, currentTilePtr->y));
	top = CheckTileToAir(currentTilePtr,GetTileAt(currentTilePtr->x, currentTilePtr->y - 1));
	bottom = CheckTileToAir(currentTilePtr,GetTileAt(currentTilePtr->x, currentTilePtr->y + 1));

	currentTilePtr->air = BoolToInt(left, right, top, bottom);

	left = CheckTileToBackgroundAir(currentTilePtr, GetTileAt(currentTilePtr->x - 1, currentTilePtr->y));
	right = CheckTileToBackgroundAir(currentTilePtr, GetTileAt(currentTilePtr->x + 1, currentTilePtr->y));
	top = CheckTileToBackgroundAir(currentTilePtr, GetTileAt(currentTilePtr->x, currentTilePtr->y - 1));
	bottom = CheckTileToBackgroundAir(currentTilePtr, GetTileAt(currentTilePtr->x, currentTilePtr->y + 1));

	currentTilePtr->noBackround = BoolToInt(left, right, top, bottom);
	
}

DOUBLE2 Chunk::GetGlobalLocation() {
	return { (double)m_X* SIZE *TILESIZE ,(double)m_Y *SIZE * TILESIZE };
}

void Chunk::RemoveTileAt(int x, int y) {
	m_TileArrPtr[x*SIZE + y]->type = Type::AIR;
}

int Chunk::GetX() {
	return m_X;
}

int Chunk::GetY() {
	return m_Y;
}

int Chunk::GetBiome() {
	return m_biome;
}

void Chunk::PlaceTileAt(int x,int y, int type) {
	GetTileAt(x, y)->type = type;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			Tile* tilePtr = GetTileAt(i, j);
			CheckSurroundings(tilePtr);
		}
	}
}


int Chunk::GetItemFromTile(int x,int y) {
	switch (GetTileAt(x,y)->type) {
	case Type::DIRT:
	case Type::GRASS:
		return 2;
		break;
	case Type::COBBLE:
		return 3;
		break;
	default:
		return 0;
	}
}