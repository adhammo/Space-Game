#include "bullet.h"

#include <list>
#include "game.h"

Bullet::Bullet(double x, double y, EntityType gunType, double gunDmg, bool isUp, double speed)
    : Entity(EntityType::Bullet, x, y, uint32_t(1), uint32_t(2), 0.0, 0.0)
	, m_up(isUp)
	, m_gunType(gunType)
	, m_gunDmg(gunDmg)
    , m_stepTime(1.0 / speed)
    , m_waitTime(1.0 / speed)
{
    /*
		up down
        +   |
        |   +
    */
    if (isUp)
    {
		const char temp[2][1] = {{'+'}, {'|'}};
        setGraphic<1, 2>(temp);
    }
    else
    {
		const char temp[2][1] = {{'|'}, {'+'}};
		setGraphic<1, 2>(temp);
    }
}
void Bullet::processInput(char special, char input) {}
void Bullet::update(double delta)
{
    m_stepTime += delta;
    if (m_stepTime >= m_waitTime)
    {
        m_stepTime = 0.0;
        double y = getYPos();

		if ((m_up && y < 0.0) || (!m_up && y + double(getHeight()) >= double(MAP_HEIGHT)))
		{
			destroy();
		}
		else
		{
			if (m_up)
				moveUp();
			else
				moveDown();
		}
    }
}
void Bullet::applyPhysics()
{
    //Check if hit something
    std::list<Entity*> hit = Game::getEntitiesInRect(getXPos(), getYPos(), getWidth(), getHeight());
    if (hit.size() != 0)
    {
        bool hitAny = false;
        for (std::list<Entity*>::iterator it = hit.begin(); it != hit.end(); it++)
        {
            if ((*it)->getType() != EntityType::Bullet && m_gunType != (*it)->getType())
            {
                hitAny = true;
				(*it)->takeDmg(m_gunDmg);
                if ((*it)->isDead())
                    (*it)->die();
            }
            else if ((*it)->getType() == EntityType::Bullet && m_gunType != ((Bullet*)(*it))->m_gunType)
            {
                hitAny = true;
				(*it)->takeDmg(m_gunDmg);
                if ((*it)->isDead())
                    (*it)->die();
            }
        }

        if (hitAny)
            destroy();
    }
}
void Bullet::draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight)
{
	render(mapData, mapWidth, mapHeight);
}
void Bullet::die()
{
    destroy();
}
void Bullet::destroy()
{
    Game::removeEntity(getId());
}
