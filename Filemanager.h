#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

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

	static FileManager* GetSingleton();

private: 
	FileManager();

	static FileManager* m_FileManagerPtr;

	std::vector<Bitmap*> m_BmpArrPtr;
	std::vector<Bitmap*> m_BmpWallArrPtr;
	std::vector<Bitmap*> m_BmpBackgroundArrPtr;
	std::vector<Bitmap*> m_BmpAvatarArrPtr;
	std::vector<Bitmap*> m_BmpNPCArrPtr;
	std::vector<Bitmap*> m_BmpItemArrPtr;
	std::vector<Bitmap*> m_BmpHUDArrPtr;
};
