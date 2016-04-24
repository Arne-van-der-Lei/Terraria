#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------
class World;
class Chunk;
class Avatar;
class HUD;
struct Tile;
class FileManager 
{
public:
	~FileManager();
	void GetAllTextures();
	Bitmap* GetBitmap(int number);
	Bitmap* GetWallBitmap(int number);
	Bitmap* GetBackgroundBitmap(int number);
	Bitmap* GetAvatarBitmap(int number);
	Bitmap* GetNPCBitmap(int number);
	Bitmap* GetItemBitmap(int number);
	Bitmap* GetHUDBitmap(int number);
	void RemoveAllTextures();

	void DrawString(String str, DOUBLE2 pos);

	void LoadWorld(World* worldPtr);
	void LoadAvatar(Avatar* avatar, HUD* hud);

	void SaveWorld(World* worldPtr);
	void SaveAvatar(Avatar* avatar, HUD* hud);

	static FileManager* GetSingleton();

	int GetIntFromString(std::string strSource, std::string value); 
	std::string GetStringFromString(std::string strSource, std::string value);
	DOUBLE2 GetDouble2FromString(std::string strSource, std::string value);
private: 
	FileManager();

	void LoadChunk(Chunk* chunkPtr, std::string str);
	void LoadTile(Tile* tilePtr, std::string str);

	std::string SaveChunk(Chunk* worldPtr);
	std::string SaveTile(Tile* tilePtr);


	static FileManager* m_FileManagerPtr;

	std::vector<Bitmap*> m_BmpArrPtr;
	std::vector<Bitmap*> m_BmpWallArrPtr;
	std::vector<Bitmap*> m_BmpBackgroundArrPtr;
	std::vector<Bitmap*> m_BmpAvatarArrPtr;
	std::vector<Bitmap*> m_BmpNPCArrPtr;
	std::vector<Bitmap*> m_BmpItemArrPtr;
	std::vector<Bitmap*> m_BmpHUDArrPtr;
};
