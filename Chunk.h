#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
class World;

struct Tile {
	unsigned int air : 4;
	unsigned int noBackround : 4;
	unsigned int x : 4;
	unsigned int y : 4;
	unsigned int type : 8;
	unsigned int backTileType : 4;
};

class Chunk 
{
public:

	enum Type {
		AIR = 0,
		DIRT = 1,
		COBBLE = 2,
		GRASS = 3
	};

	enum BackgroundType {
		BAIR = 0,
		BDIRT = 1
	};

	enum BiomeType {
		mountains = 0
	};

	enum Side {
		LEFT = 1,
		RIGHT = 2,
		TOP = 4,
		BOTTOM = 8
	};

	Chunk(int x, int y, World * worldPtr);
	virtual ~Chunk( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Chunk( const Chunk& ) = delete;
	Chunk& operator=( const Chunk& ) = delete;

	static const int SIZE = 16;
	static const int TILESIZE = 32;

	void Tick(double deltaTime);
	void Paint();
	void PaintBackground();
	Tile* GetTileAt(int x, int y);
	void RemoveTileAt(int x, int y);
	void AfterInit();
	void DigTileAt(int x, int y);
	void PlaceTileAt(int x, int y, int type);

	int GetItemFromTile(int x, int y);
	int GetX();
	int GetY();
	int GetBiome();

private: 

	std::vector<Tile*> m_TileArrPtr;
	World * m_WorldPtr = nullptr; 
	int m_X = 0;
	int m_Y = 0;
	int m_biome = 0;

	bool CheckTileToAir(Tile* currentTilePtr, Tile* tilePtr);
	bool CheckTileToBackgroundAir(Tile* currentTilePtr, Tile* tilePtr);

	int BoolToInt(bool left, bool right, bool top, bool bottom);
	void CheckSurroundings(Tile* currentTilePtr);

	void CalculateBorder();

	DOUBLE2 GetGlobalLocation();

	void PaintTileAt(Tile* tilePtr);
	void PaintBackgroundAt(Tile* tilePtr);

};
