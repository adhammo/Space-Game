#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class Bullet : public Entity
{
public:
    Bullet(double x, double y, EntityType gunType, double gunDmg, bool isUp, double speed);

public: //Entity behavior
    void processInput(char special, char input);
    void update(double delta);
    void applyPhysics();
    void draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight);
    void die();
    void destroy();

private:
    bool m_up;
	EntityType m_gunType;
	double m_gunDmg;
    double m_stepTime;
    double m_waitTime;
};

#endif // BULLET_H
