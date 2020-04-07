#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity
{
public:
    Enemy();
	Enemy(double x, double y);
	Enemy(double x, double y, double maxHp, double dmg, double moveSpeed, double reloadTime, double bulletSpeed);

public: //Entity behavior
	void processInput(char special, char input);
	void update(double delta);
	void applyPhysics() {}
	void draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight);
	void die();
	void destroy();

public: //Enemy Functionality
    void fire();

public: //Getters
	double getReloadTime() const { return m_reloadTime; }

public: //Setters
	void setReloadTime(double reloadTime) { m_reloadTime = reloadTime; }

private: //Members
	double m_fireTime;
	double m_reloadTime;
	double m_bulletSpeed;
};

#endif // ENEMY_H
