#pragma once

#include "Components.h"
#include "SpriteRenderer.h"
#include "SDL.h"

class ScreenWrapign : public Component
{
public:
	
	void SetScreenSize(int xSize, int ySize)
	{
		_screenWidhth = xSize;
		_screenHight = ySize;
	}

	void WrapWindow(Transform* objTransform)
	{
		float objXpos = objTransform->position.x();
		float objYpos = objTransform->position.y();

		#pragma region Y-AxisWraping
		//Teleports up
		if (objYpos > _screenHight)
		{
			objTransform->position.y() = 0;
		}

		//Teleports down
		if (objYpos < 0)
		{
			objTransform->position.y() = _screenHight;
		}
#pragma endregion
		#pragma region X-AxisWraping
		//Teleports up
		if (objXpos > _screenHight)
		{
			objTransform->position.x() = 0;
		}

		//Teleports down
		if (objXpos < 0)
		{
			objTransform->position.x() = _screenWidhth;
		}
#pragma endregion
	}

private:
	int _screenWidhth = 0;
	int _screenHight = 0;
};
