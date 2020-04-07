#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <inttypes.h>
#include <math.h>
#include <float.h>
#include "point.h"

class TransformComponent
{
public:
	TransformComponent() : m_x(0.0), m_y(0.0), m_width(0), m_height(0), m_moveSpeed(1.0) {}
	TransformComponent(double x, double y, uint32_t width, uint32_t height, double moveSpeed = 1.0) : m_x(x), m_y(y), m_width(width), m_height(height), m_moveSpeed(fabs(moveSpeed)) {}

public: //Movement
	inline void moveUp() { m_y -= m_moveSpeed; }
	inline void moveDown() { m_y += m_moveSpeed; }
	inline void moveLeft() { m_x -= m_moveSpeed; }
	inline void moveRight() { m_x += m_moveSpeed; }

public: //Logic
	inline bool containsPoint(double x, double y) const { return (x >= m_x) && (x <= m_x + double(m_width)) && (y >= m_y) && (y <= m_y + double(m_height)); }
	inline bool intersects(double x, double y, uint32_t width, uint32_t height) const { return ((x - m_x) < 0 ? ((m_x - x) < double(width)) : ((x - m_x) < double(m_width))) && ((y - m_y) < 0 ? ((m_y - y) < double(height)) : ((y - m_y) < double(m_height))); }

public: //Setters
	inline void setPos(FPoint point) { m_x = point.x; m_y = point.y; }
	inline void setPos(double x, double y) { m_x = x; m_y = y; }
	inline void setXPos(double x) { m_x = x; }
	inline void setYPos(double y) { m_y = y; }

	inline virtual void setSize(const Point& size) { m_width = abs(size.x); m_height = abs(size.y); }
	inline virtual void setSize(uint32_t width, uint32_t height) { m_width = width; m_height = height; }
	inline virtual void setWidth(uint32_t width) { m_width = width; }
	inline virtual void setHeight(uint32_t height) { m_height = height; }
	inline void setMoveSpeed(double moveSpeed) { m_moveSpeed = fabs(moveSpeed); }

public: //Getters
	inline FPoint getPos() const { return FPoint(m_x, m_y); }
	inline double getXPos() const { return m_x; }
	inline double getYPos() const { return m_y; }
	inline double getMovementSpeed() const { return m_moveSpeed; }
	inline uint32_t getWidth() const { return m_width; }
	inline uint32_t getHeight() const { return m_height; }

private: //Members
	double m_x;
	double m_y;
	double m_moveSpeed;
	uint32_t m_width;
	uint32_t m_height;
};

#endif //TRANSFORMCOMPONENT_H