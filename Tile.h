#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

class Tile 
{
public:

	enum class Type{
		DIRT,
		COBBLE
	};

	Tile( DOUBLE2 position, int x, int y, Bitmap* bitmap, Type type);
	virtual ~Tile( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Tile( const Tile& ) = delete;
	Tile& operator=( const Tile& ) = delete;

	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual Type GetType();
	virtual void AfterInit();

	static const int SIZE = 32.0;

private: 

	Bitmap* m_BmpPtr = nullptr;
	DOUBLE2 m_Pos;
	DOUBLE2 m_WorldPos;

	PhysicsActor* m_ActPtr = nullptr;

	Type m_Type = Type::DIRT;
	int m_Rand = 0;

	int m_Byte;

	bool CheckTileToAir( Tile* tile);
	int BoolToInt(bool left, bool right, bool top, bool bottom, bool dLeft, bool dRight, bool dTop, bool dBottom);
	int CheckSurroundings();
	bool CheckTileToDirt(Tile* tile);
};
