//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Tile.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Tile::Tile(DOUBLE2 position, int x, int y, Bitmap* bitmap, Type type) : m_WorldPos(position), m_BmpPtr(bitmap), m_Pos({ (double)x,(double)y }), m_Type(type), m_Rand(rand()%3)
{
}

Tile::~Tile()
{
	delete m_ActPtr;
	m_ActPtr = nullptr;

	delete m_BmpPtr;
	m_BmpPtr = nullptr;
}

void Tile::AfterInit() {
	m_Byte = CheckSurroundings();

	std::cout << m_Byte << std::endl;

	if (m_Byte < 15) {
		m_ActPtr = new PhysicsActor(m_WorldPos, 0, BodyType::STATIC);
		m_ActPtr->AddBoxFixture(SIZE, SIZE, 0);
	}
}

void Tile::Tick(double deltaTime)
{

}

void Tile::Paint()
{
	MATRIX3X2 matWorld,matTrans,matScale,matcenter;

	matcenter.SetAsTranslate(-8, -8);
	matTrans.SetAsTranslate(m_WorldPos);
	matScale.SetAsScale(2);

	RECT2 rect;
	rect.left = m_Byte*SIZE /2;
	rect.top = m_Rand*SIZE / 2;
	rect.right = m_Byte*SIZE / 2 + SIZE / 2;
	rect.bottom = m_Rand *SIZE / 2 + SIZE / 2;

	matWorld = matcenter* matScale * matTrans;
	
	GAME_ENGINE->SetWorldMatrix(matWorld);
	GAME_ENGINE->DrawBitmap(m_BmpPtr,rect);
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

Tile::Type Tile::GetType() {
	return m_Type;
}

bool Tile::CheckTileToAir(Tile* tile) {
	if (tile != nullptr) {
		if (tile->GetType() == m_Type || m_Type == Type::DIRT) {
			return true;
		}
	}
	return false;
}

bool Tile::CheckTileToDirt(Tile* tile) {
	if (tile != nullptr) {
		if (tile->GetType() == Type::DIRT) {
			return true;
		}
	}
	return false;
}

int Tile::BoolToInt(bool left, bool right, bool top, bool bottom,bool dLeft, bool dRight, bool dTop, bool dBottom ) {
	int c = 0;
	if (left)
		c |= 1 << 0;
	if (right)
		c |= 1 << 1;
	if (top)
		c |= 1 << 2;
	if (bottom)
		c |= 1 << 3;
	if (dLeft)
		c |= 1 << 4;
	if (dRight)
		c |= 1 << 5;
	if (dTop)
		c |= 1 << 6;
	if (dBottom)
		c |= 1 << 7;
	return c;
}

int Tile::CheckSurroundings() {

	/*bool left, right, top, bottom, dLeft, dRight, dTop, dBottom;

	left = CheckTileToAir(m_ChunkPtr->GetTileAt(m_Pos.x - 1, m_Pos.y));
	right = CheckTileToAir(m_ChunkPtr->GetTileAt(m_Pos.x + 1, m_Pos.y));
	top = CheckTileToAir(m_ChunkPtr->GetTileAt(m_Pos.x, m_Pos.y - 1));
	bottom = CheckTileToAir(m_ChunkPtr->GetTileAt(m_Pos.x, m_Pos.y + 1));

	dLeft = CheckTileToDirt(m_ChunkPtr->GetTileAt(m_Pos.x - 1, m_Pos.y));
	dRight = CheckTileToDirt(m_ChunkPtr->GetTileAt(m_Pos.x + 1, m_Pos.y));
	dTop = CheckTileToDirt(m_ChunkPtr->GetTileAt(m_Pos.x, m_Pos.y - 1));
	dBottom = CheckTileToDirt(m_ChunkPtr->GetTileAt(m_Pos.x, m_Pos.y + 1));

	*/return 0;//BoolToInt(left, right, top, bottom, dLeft, dRight, dTop, dBottom);
}