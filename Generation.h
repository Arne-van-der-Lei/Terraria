#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

#include "World.h"
#include "Chunk.h"

class Generation 
{
public:
	Generation( );
	virtual ~Generation( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Generation( const Generation& ) = delete;
	Generation& operator=( const Generation& ) = delete;

	static void GenerateChunks(World* worldPtr);
private: 

	static int checkSides(int x, int y, Chunk* chunkPtr);
	static void Smooth(int less, int bigg, World* world);
	static void GenerateTileAt(int i, int j, Chunk* chunkPtr);
	static const int seed = 31;
};
