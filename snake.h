#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <deque>
using namespace sf;
using namespace glm;
class snake
{
public:
	vec3 getPosition();
	void setPosition(vec3 newPos);
	void addToPosition(vec3 add);
	void setDirection(vec4 newDirection);
	void addToDirection(vec4 addingVector);
	vec4 getDirection();
	void setPathLength(UINT length);
	void drawSnake();
	static void drawCube();
	snake(vec3 pos);
	void move(float x, float y, float z, float moveSpeed);

private:
	vec3 position;
	vec4 direction = vec4(0,0,0,0);
	std::deque<vec3> positionHistory;
	std::deque<vec4> directionHistory;
	void writePathHistory();
	UINT pathLength = 0;
};

