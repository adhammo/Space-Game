#ifndef ENTITY_H
#define ENTITY_H

#include <inttypes.h>
#include "transformcomponent.h"
#include "lifecomponent.h"
#include "entitytype.h"
#include "gamesettings.h"

class Entity : public TransformComponent, public LifeComponent
{
private: //Entities Counter
	static uint32_t counter;

public: //Entities Counter Reset
	static void resetCounter() { counter = 0; }

public:
	Entity(EntityType type) : m_id(counter++), m_type(type) { m_graphic = new char[0]; }
	Entity(EntityType type, double x, double y, uint32_t width, uint32_t height, double maxHp, double dmg) : TransformComponent(x, y, width, height), LifeComponent(maxHp, dmg), m_id(counter++), m_type(type) { m_graphic = new char[width * height]; }
	Entity(EntityType type, double x, double y, uint32_t width, uint32_t height, double moveSpeed, double maxHp, double dmg) : TransformComponent(x, y, width, height, moveSpeed), LifeComponent(maxHp, dmg), m_id(counter++), m_type(type) { m_graphic = new char[width * height]; }
	Entity(EntityType type, double x, double y, uint32_t width, uint32_t height, double moveSpeed, double maxHp, double hp, double dmg) : TransformComponent(x, y, width, height, moveSpeed), LifeComponent(maxHp, hp, dmg), m_id(counter++), m_type(type) { m_graphic = new char[width * height]; }
	virtual ~Entity() { delete[] m_graphic; }

public: //Functionality
    virtual void processInput(char special, char input) {}
    virtual void update(double delta) {}
    virtual void applyPhysics() {}
    virtual void draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight) {}
    virtual void die() {}
    virtual void destroy() {}

public: //Render
	void render(char* mapData, uint32_t mapWidth, uint32_t mapHeight);

public: //Equallity
	inline bool operator==(const Entity& rhs) { return (m_id == rhs.m_id); }

public: //Graphic Setters
    template <int width, int height>
	void setGraphic(const char (&data)[height][width]);
	void setGraphic(const char* data, uint32_t dataWidth, uint32_t dataHeight);
	void setGraphic(const char* str);

public: //Size Setters
	inline void setSize(const Point& size) { TransformComponent::setSize(size); delete[] m_graphic; m_graphic = new char[getWidth() * getHeight()]; }
	inline void setSize(uint32_t width, uint32_t height) { TransformComponent::setSize(width, height); delete[] m_graphic; m_graphic = new char[getWidth() * getHeight()]; }
	inline void setWidth(uint32_t width) { TransformComponent::setWidth(width); delete[] m_graphic; m_graphic = new char[getWidth() * getHeight()]; }
	inline void setHeight(uint32_t height) { TransformComponent::setHeight(height); delete[] m_graphic; m_graphic = new char[getWidth() * getHeight()]; }

public: //Getters
    inline int getId() const { return m_id; }
    inline EntityType getType() const { return m_type; }
    inline const char* getGraphic() const { return m_graphic; }

private: //Members
    uint32_t m_id;
    EntityType m_type;
	char* m_graphic;
};

template <int width, int height>
void Entity::setGraphic(const char(&data)[height][width])
{
	uint32_t graphicWidth = getWidth();
	uint32_t graphicHeight = getHeight();

	for (uint32_t i = 0; i < graphicHeight; i++)
	{
		for (uint32_t j = 0; j < graphicWidth; j++)
			m_graphic[(i * graphicWidth) + j] = (char)32;
	}

	for (uint32_t i = 0; i < height; i++)
	{
		for (uint32_t j = 0; j < width; j++)
			m_graphic[(i * graphicWidth) + j] = data[i][j];
	}
}

#endif // ENTITY_H
