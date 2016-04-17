#pragma once
//-----------------------------------------------------------------
// Student data
// Name: van der Lei Arne
// Group: 1DAE16
//-----------------------------------------------------------------

#include "Avatar.h"

class Camera 
{
public:
	Camera( );
	virtual ~Camera( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Camera( const Camera& ) = delete;
	Camera& operator=( const Camera& ) = delete;

	void SetViewMatrix(Avatar* avatarPtr);
private: 
	DOUBLE2 ClampToLevel(DOUBLE2 pos);

};
