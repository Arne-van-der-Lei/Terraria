#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
class Chunk;
class Avatar;
class Background;
class World 
{
public:
	World( );
	virtual ~World( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	World( const World& ) = delete;
	World& operator=( const World& ) = delete;

	void Tick(double deltaTime,Avatar* avatarPtr);
	void Paint(int x,int y);
	void PaintBackground(Avatar* avatarPtr);

	static const size_t WIDTH = 20;
	static const size_t HEIGHT = 20;

	Chunk* GetChunkAt(int x, int y);
	Chunk* GetChunkAt(DOUBLE2 pos);

	std::vector<Chunk* > GetChunks();

private: 
	Background* m_Bg;
	Background* m_FrontBg;
	std::vector<Chunk* > m_ChunkArrPtr;
};
