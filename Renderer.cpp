#include "Renderer.h"
#include <iostream>
#include "io.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Renderer.h"
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace sf;
using namespace glm;

bool Renderer::paused = false;
vec3 camDirection({ 0,0,0 });
vec3 position({ 0,0,0.f });
vec3 Renderer::orientation = { 0,0,0 }; //1.5pi to look backward on z axis
mat4 projectionMtx;
mat4 modelViewMtx;
float Renderer::camSpeed = 0.04f;
float moveSpeed = 1.1f;

mat4 Renderer::getViewMatrix()
{
    //Convert 2 axis inputs into 3 axis spherical rotation with radius == 1
    camDirection = vec3
    (
        25*cos(orientation.x) * cos(orientation.y),
        25*sin(orientation.y),
        25*sin(orientation.x) * cos(orientation.y)
    );
    mat4 look = lookAt
    (
        position + camDirection,
        position,
        vec3(0.0f, 1.0f, 0.0f)
    );
    return look;
}

void Renderer::initRenderer(Window& window)
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mat4 ViewMatrix = getViewMatrix();
    glLoadMatrixf(value_ptr(ViewMatrix));
}

void Renderer::Render(Window& window, vec3 playerPosition)
{
    position = playerPosition; //Set cam position to player position
    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    projectionMtx = perspectiveFov(radians(45.0f), (float)window.getSize().x, (float)window.getSize().y, 0.1f, 1000.f);
    glLoadMatrixf(value_ptr(projectionMtx));
    initRenderer(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Move(float x, float y, float z)
{
    vec3 offset = { 0.f,0.f,0.f };

    vec3 forward = vec3(cos(orientation.x) * cos(orientation.y), sin(orientation.y), sin(orientation.x) * cos(orientation.y));
    vec3 right = vec3(-forward.z, 0, forward.x);

    offset += x * right;
    offset += y * forward;
    offset.y += z;

    normalize(offset);
    offset *= moveSpeed;
    position += offset;
}

void Renderer::drawGrid(float width, float height, UINT16 partitions_x, UINT16 partitions_y, float position_y)
{
    glLineWidth(2.0f);
    glPointSize(2.0f);
    glBegin(GL_LINE_STRIP); //Main outside square
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(-width, position_y, -height);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(-width, position_y, height);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(width, position_y, height);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(width, position_y, -height);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(-width, position_y, -height);
    glEnd();
    glBegin(GL_LINES);
    float step_x = width / partitions_x * 2; //*2 as radius is half diameter, which is full length
    float step_y = height / partitions_y * 2; //*2 as radius is half diameter, which is full length
    for (UINT16 i = 0; i < partitions_x; i++)
    {
        float x = -width + (step_x*i);
        glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(x, position_y, -height); //gridline x pt 1
        glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(x, position_y, height); //gridline x pt 2
    }
    for (UINT16 i = 0; i < partitions_y; i++)
    {
        float y = -height + (step_y * i);
        glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(width, position_y, y); //gridline z  pt 1
        glColor4f(0.5f, 0.5f, 0.5f, 1.0f); glVertex3f(-width, position_y, y); //gridline z pt 2
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}