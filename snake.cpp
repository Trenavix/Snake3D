#include "snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include <iostream>
using namespace sf;
using namespace glm;

snake::snake(vec3 pos)
{
	position = pos;
    direction = vec4(0, 0, 0, 0);
}

vec3 snake::getPosition()
{
	return position;
}

void snake::setPosition(vec3 newPos)
{
	position = newPos;
}

void snake::setDirection(vec4 newDirection)
{
    direction = newDirection;
}

void snake::addToDirection(vec4 addingVector)
{
    direction += addingVector;
}

vec4 snake::getDirection()
{
    return direction;
}

void snake::addToPosition(vec3 add)
{
	position += add;
    writePathHistory();
}

void snake::drawSnake()
{
    for (UINT i = 0; i < positionHistory.size(); i++)
    {
        vec3 pos = positionHistory.at(i);
        vec4 dir = directionHistory.at(i);
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glPushMatrix();
        glRotatef(degrees(dir.w), dir.x, dir.y, dir.z);
        snake::drawCube();
        glPopMatrix();
        glPopMatrix();
    }
    
}

void snake::writePathHistory()
{
    positionHistory.push_front(position);
    directionHistory.push_front(direction);
    if (positionHistory.size() > pathLength)
    {
        positionHistory.pop_back();
        directionHistory.pop_back();
    }
}

void snake::setPathLength(UINT newLength)
{
    pathLength = newLength;
}


void snake::move(float x, float y, float z, float moveSpeed)
{
    vec3 offset = { 0.f,0.f,0.f };

    vec3 forward = vec3(cos(Renderer::orientation.x), 0, sin(Renderer::orientation.x));
    vec3 right = vec3(-forward.z, 0, forward.x);

    offset += x * right;
    offset += y * forward;
    offset.y += z;

    normalize(offset);
    offset *= moveSpeed;
    position += offset; if (positionHistory.size() > 1)
    {
        vec3 difVec = position - positionHistory.at(1);
        normalize(difVec);
        vec3 unitY = vec3(0, 1, 0);
        vec3 crossVec = cross(unitY, difVec);
        float theta = acos(dot(unitY, difVec));
        direction = vec4(crossVec, theta);
    }
    writePathHistory();
    
    
}

void snake::drawCube()
{
    glBegin(GL_QUADS);
    //front
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    //right side
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    //back side
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    //left side
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    //top
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    //bottom (not needed)
    /*glColor4f(0.0f, 0.0f, 0.0f, 1.0f); glVertex3f(-18.0f, -7.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-18.0f, -5.0f, -1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3f(-18.0f, -5.0f, 1.0f);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f); glVertex3f(-18.0f, -7.0f, 1.0f);*/
    glEnd();
}
