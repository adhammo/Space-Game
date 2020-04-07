#include "entity.h"

uint32_t Entity::counter = 0;

#define min(x,y) ((x) < (y) ? (x) : (y))

void Entity::render(char* mapData, uint32_t mapWidth, uint32_t mapHeight)
{
	if (!intersects(0.0, 0.0, MAP_WIDTH, MAP_HEIGHT))
		return;

	uint32_t x = uint32_t(getXPos());
	uint32_t y = uint32_t(getYPos());
	uint32_t width = getWidth();
	uint32_t height = getHeight();

	for (uint32_t i = y; i < min((y + height), mapHeight); i++)
		for (uint32_t j = x; j < min((x + width), mapWidth); j++)
			mapData[(i * mapWidth) + j] = m_graphic[(i - y) * width + (j - x)];
}
void Entity::setGraphic(const char* data, uint32_t dataWidth, uint32_t dataHeight)
{
	uint32_t graphicWidth = getWidth();
	uint32_t graphicHeight = getHeight();

	for (uint32_t i = 0; i < graphicHeight; i++)
	{
		for (uint32_t j = 0; j < graphicWidth; j++)
			m_graphic[(i * graphicWidth) + j] = (char)32;
	}

	for (uint32_t i = 0; i < dataHeight; i++)
	{
		for (uint32_t j = 0; j < dataWidth; j++)
			m_graphic[(i * graphicWidth) + j] = data[(i * dataWidth) + j];
	}
}
void Entity::setGraphic(const char* str)
{
	char temp;
	uint32_t graphicWidth = getWidth();
	uint32_t graphicHeight = getHeight();

	for (uint32_t i = 0; i < graphicHeight; i++)
	{
		for (uint32_t j = 0; j < graphicWidth; j++)
			m_graphic[(i * graphicWidth) + j] = (char)32;
	}

	for (uint32_t i = 0; i < graphicHeight; i++)
	{
		for (uint32_t j = 0; j < graphicWidth; j++)
		{
			temp = str[(i * graphicWidth) + j];
			if (temp != '\0') m_graphic[(i * graphicWidth) + j] = temp;
			else return;
		}
	}
}