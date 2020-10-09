#include "io.h"
#include <iostream>
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "snake.h"
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtx/string_cast.hpp"
#include "XInputMapping.h"

XInputMapping* io::Player1;
float io::moveSpeed = 0.5f;
float io::rotateSpeed = 0.05f;
WORD io::buttonKeyFrame = 0;

void io::storeButtonFrame(XInputMapping* controller)
{
    buttonKeyFrame = controller->GetState().Gamepad.wButtons;
}

bool io::buttonDown(WORD XInputButtons, WORD button)
{
    return ((XInputButtons & button) - (buttonKeyFrame & button) > 0);
}

void io::readMainInputs(XInputMapping* controller, UINT framecount)
{
    if (buttonDown(controller->GetState().Gamepad.wButtons, XINPUT_GAMEPAD_START)) 
        Renderer::paused = !Renderer::paused;
    storeButtonFrame(controller);
}

void io::readSnakeInputs(snake& currentSnake, UINT framecount, XInputMapping* controller)
{
    if (controller->IsConnected())
    {
        XINPUT_STATE state = controller->GetState();
        INT16 LanalogX = state.Gamepad.sThumbLX;
        INT16 LanalogY = state.Gamepad.sThumbLY;
        INT16 RanalogX = state.Gamepad.sThumbRX;
        INT16 RanalogY = state.Gamepad.sThumbRY;
        INT16 RTrigger = state.Gamepad.bRightTrigger;
        //snake all axis movement
        currentSnake.move(-(float)LanalogX / 32767.f, -0.8f-(float)RTrigger/127.5f, (float)LanalogY / 32767.f, moveSpeed); 
        //camera movement
        Renderer::orientation.x += Renderer::camSpeed*((float)RanalogX/32767.f); //x camera
        Renderer::orientation.y += Renderer::camSpeed * ((float)-RanalogY / 32767.f); //y camera
    }
    else
    {
        //TODO: Keyboard controls
        if (Keyboard::isKeyPressed(Keyboard::Right)) Renderer::orientation.x += Renderer::camSpeed;
        if (Keyboard::isKeyPressed(Keyboard::Left)) Renderer::orientation.x -= Renderer::camSpeed;
        if (Keyboard::isKeyPressed(Keyboard::Up)) Renderer::orientation.y += Renderer::camSpeed;
        if (Keyboard::isKeyPressed(Keyboard::Down)) Renderer::orientation.y -= Renderer::camSpeed;
    }
}