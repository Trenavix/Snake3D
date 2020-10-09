#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

using namespace sf;
class Renderer
{
public:
	static glm::mat4 getViewMatrix();
	static void initRenderer(Window& window);
	static void Render(Window& window, glm::vec3 playerPosition);
	static void drawGrid(float width, float height, UINT16 partitions_x, UINT16 partitions_y, float position_y);
	static void Move(float x, float y, float z);
	static glm::vec3 orientation;
	static float camSpeed;
	static bool paused;
};
