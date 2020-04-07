#include "enemy.h"

#include "bullet.h"
#include "game.h"

Enemy::Enemy()
    : Entity(EntityType::Enemy, 0.0, 0.0, uint32_t(4), uint32_t(2), 1.0, 20.0, 10.0)
    , m_fireTime(2.5)
    , m_reloadTime(3.0)
    , m_bulletSpeed(5.0)
{
    /*
        <[]>
         ..
    */
	const char temp[2][4] = {{'<', '[', ']', '>'}, {' ', '.', '.', ' '}};
    setGraphic<4,2>(temp);
}
Enemy::Enemy(double x, double y)
	: Entity(EntityType::Enemy, x, y, uint32_t(4), uint32_t(2), 1.0, 20.0, 10.0)
    , m_fireTime(2.5)
    , m_reloadTime(3.0)
    , m_bulletSpeed(5.0)
{
    /*
        <[]>
         ..
    */
	const char temp[2][4] = {{'<', '[', ']', '>'}, {' ', '.', '.', ' '}};
	setGraphic<4, 2>(temp);
}
Enemy::Enemy(double x, double y, double maxHp, double dmg, double moveSpeed, double reloadTime, double bulletSpeed)
	: Entity(EntityType::Enemy, x, y, uint32_t(4), uint32_t(2), moveSpeed, maxHp, dmg)
    , m_fireTime(reloadTime * 0.9f)
    , m_reloadTime(reloadTime)
    , m_bulletSpeed(bulletSpeed)
{
    /*
        <[]>
         ..
    */
	const char temp[2][4] = {{'<', '[', ']', '>'}, {' ', '.', '.', ' '}};
	setGraphic<4, 2>(temp);
}

//Enemy Functionality
void Enemy::fire()
{
    //Check reload time
    if (m_fireTime  >= m_reloadTime)
    {
        m_fireTime = 0;
        //Instantiate 2 bullets
		double x = getXPos();
		double y = getYPos();
		double dmg = getDmg();
        Bullet* bullet1 = new Bullet(x + 1.0, y + 2.0, EntityType::Enemy, dmg, false, m_bulletSpeed);
        Bullet* bullet2 = new Bullet(x + 2.0, y + 2.0, EntityType::Enemy, dmg, false, m_bulletSpeed);
        Game::addEntity(bullet1);
        Game::addEntity(bullet2);
    }
}

//Entity behavior
void Enemy::update(double delta)
{
    m_fireTime += delta;
    fire();
}
void Enemy::processInput(char special, char input)
{
}
void Enemy::draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight)
{
	render(mapData, mapWidth, mapHeight);
}
void Enemy::die()
{
    destroy();
}
void Enemy::destroy()
{
    Game::removeEntity(getId());
}
