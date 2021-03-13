#pragma once

#include "Components.h"
#include "SpriteRenderer.h"
#include "SDL.h"

class ScreenWrapign : public Component
{
public:
	/// <summary>
	/// Gets the size of the playable window
	/// </summary>
	/// <param name="xSize"></param>
	/// <param name="ySize"></param>
	void GetScreenSize(int xSize, int ySize)
	{
		_screenWidhth = xSize;
		_screenHight = ySize;
	}

	/// <summary>
	/// Moves the object to the other side of the screen when it is about to move out of the play area
	/// </summary>
	/// <param name="objTransform"></param>
	void WrapWindow(Transform* objTransform)
	{
		#pragma region Y-AxisWraping
		
		//Teleports up
		if (objTransform->position.y() > _screenHight)
		{
			objTransform->position.y() = 0;
		}

		//Teleports down
		if (objTransform->position.y() < 0)
		{
			objTransform->position.y() = _screenHight;
		}

#pragma endregion
		#pragma region X-AxisWraping

		//Teleports up
		if (objTransform->position.x() > _screenWidhth)
		{
			objTransform->position.x() = 0;
		}

		//Teleports down
		if (objTransform->position.x() < 0)
		{
			objTransform->position.x() = _screenWidhth;
		}

#pragma endregion
	}

private:
	int _screenWidhth = 0;
	int _screenHight = 0;
};
