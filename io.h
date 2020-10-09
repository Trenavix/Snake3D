#pragma once
#include <SFML/Graphics.hpp>
#include "snake.h"
#include "XInputMapping.h"
using namespace sf;
class io
{
public:
	static void readSnakeInputs(snake& currentSnake, UINT framecount, XInputMapping* controller);
	static void readMainInputs(XInputMapping* controller, UINT framecount);
private:
	static float moveSpeed;
	static XInputMapping* Player1;
	static float rotateSpeed;
	static void storeButtonFrame(XInputMapping* controller);
	static WORD buttonKeyFrame;
	static bool buttonDown(WORD XInputButtons, WORD button);
};

