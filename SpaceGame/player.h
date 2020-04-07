#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player();
    Player(double x, double y);
    Player(double x, double y, double maxHp, double dmg, double moveSpeed, double reloadTime, double bulletSpeed);

public: //Entity behavior
    void processInput(char special, char input);
    void update(double delta);
    void applyPhysics() {}
    void draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight);
    void die();
    void destroy();

public: //Player Functionality
    void fire();

public: //Getters
    double getReloadTime() const { return m_reloadTime; }

public: //Setters
    void setReloadTime(double reloadTime) { m_reloadTime = reloadTime; }

private: //Members
    FPoint m_pos;
    Point m_velocity;
    double m_fireTime;
    double m_reloadTime;
    double m_bulletSpeed;
};

#endif // PLAYER_H
