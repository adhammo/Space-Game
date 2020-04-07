#include "player.h"

#include "bullet.h"
#include "game.h"

Player::Player()
    : Entity(EntityType::Player, 0.0, 0.0, (uint32_t)3, (uint32_t)2, 10.0, 200.0, 100.0)
	, m_pos(0.0, 0.0)
    , m_velocity(0, 0)
    , m_fireTime(0.1f)
    , m_reloadTime(0.1f)
    , m_bulletSpeed(10)
{
    /*
         .
        <->
    */
	const char temp[2][3] = {{' ', '.', ' '}, {'<', '-', '>'}};
    setGraphic<3, 2>(temp);
}
Player::Player(double x, double y)
	: Entity(EntityType::Player, x, y, uint32_t(3), uint32_t(2), 10.0, 200.0, 100.0)
	, m_pos(x, y)
	, m_velocity(0, 0)
    , m_fireTime(0.1f)
    , m_reloadTime(0.1f)
    , m_bulletSpeed(10)
{
    /*
         .
        <->
    */
	const char temp[2][3] = {{' ', '.', ' '}, {'<', '-', '>'}};
	setGraphic<3, 2>(temp);
}
Player::Player(double x, double y, double maxHp, double dmg, double moveSpeed, double reloadTime, double bulletSpeed)
	: Entity(EntityType::Player, x, y, uint32_t(3), uint32_t(2), moveSpeed, maxHp, dmg)
	, m_pos(x, y)
	, m_velocity(0, 0)
    , m_fireTime(reloadTime)
    , m_reloadTime(reloadTime)
    , m_bulletSpeed(bulletSpeed)
{
    /*
         .
        <->
    */
	const char temp[2][3] = {{' ', '.', ' '}, {'<', '-', '>'}};
	setGraphic<3, 2>(temp);
}

//Player Functionality
void Player::fire()
{
    //Check reload time
    if (m_fireTime >= m_reloadTime)
    {
        m_fireTime = 0.0;

        //Instantiate new bullet
        Bullet* bullet = new Bullet(getXPos() + 1.0, getYPos() - 1.0, EntityType::Player, getDmg(), true, m_bulletSpeed);
        Game::addEntity(bullet);
    }
}

//Entity behavior
void Player::update(double delta)
{
    //Increment fire time
    m_fireTime += delta;

	double x = getXPos();
	double y = getYPos();
	uint32_t width = getWidth();
	uint32_t height = getHeight();

	if (m_velocity.x == -1 && x <= 0.0)
	{
		m_velocity.x = 0;
		m_pos.x = 0.0;
	}
	else if (m_velocity.x == 1 && x + double(width) >= double(MAP_WIDTH))
	{
		m_velocity.x = 0;
		m_pos.x = double(MAP_WIDTH) - double(width);
	}

	if (m_velocity.y == -1 && y <= 0.0)
	{
		m_velocity.y = 0;
		m_pos.y = 0.0;
	}
	else if (m_velocity.y == 1 && y + double(height) >= double(MAP_HEIGHT))
	{
		m_velocity.y = 0;
		m_pos.y = double(MAP_HEIGHT) - double(height);
	}

    if (m_velocity.x != 0)
    {
        std::list<Entity*> hit;
        if (m_velocity.x == 1)
            hit = Game::getEntitiesInRect(x + 1, y, width, height);
        else
            hit = Game::getEntitiesInRect(x - 1, y, width, height);

        if (hit.size() != 0)
        {
            bool hitAny = false;
            for (std::list<Entity*>::iterator it = hit.begin(); it != hit.end(); it++)
            {
                if ((*it)->getId() != getId() && (*it)->getType() == EntityType::Enemy)
                {
                    hitAny = true;
                    m_pos.x = double(x);
                    break;
                }
            }

            if (!hitAny)
                m_pos.x += m_velocity.x * getMovementSpeed() * delta;
        }
        else
            m_pos.x += m_velocity.x * getMovementSpeed() * delta;
    }
    else if (m_velocity.y != 0)
    {
        std::list<Entity*> hit;
        if (m_velocity.y == 1)
            hit = Game::getEntitiesInRect(x, y + 1, width, height);
        else
            hit = Game::getEntitiesInRect(x, y - 1, width, height);
        if (hit.size() != 0)
        {
            bool hitAny = false;
            for (std::list<Entity*>::iterator it = hit.begin(); it != hit.end(); it++)
            {
                if ((*it)->getId() != getId() && (*it)->getType() == EntityType::Enemy)
                {
                    hitAny = true;
                    m_pos.y = double(y);
                    break;
                }
            }

            if (!hitAny)
                m_pos.y += m_velocity.y * getMovementSpeed() * delta;
        }
        else
            m_pos.y += m_velocity.y * getMovementSpeed() * delta;
    }

	setPos((uint32_t)(m_pos.x + 0.5f), (uint32_t)(m_pos.y + 0.5f));
}

void Player::processInput(char special, char input)
{
    //Normal keys
    if ((int)special == 0)
    {
        switch (input)
        {
        case 'w':
        case 'W':
            m_velocity.x = 0;
            m_velocity.y = -1;
            break;
        case 's':
        case 'S':
            m_velocity.x = 0;
            m_velocity.y = 1;
            break;
        case 'd':
        case 'D':
            m_velocity.x = 1;
            m_velocity.y = 0;
            break;
        case 'a':
        case 'A':
            m_velocity.x = -1;
            m_velocity.y = 0;
            break;
        case ' ':
            fire();
            m_velocity.x = 0;
            m_velocity.y = 0;
            break;
        case 'f':
        case 'F':
            m_velocity.x = 0;
            m_velocity.y = 0;
            break;
        }
    }
    //Arrows
    else if ((int)special == -32)
    {

        switch ((int)input)
        {
        case 72:
            m_velocity.x = 0;
            m_velocity.y = -1;
            break;
        case 80:
            m_velocity.x = 0;
            m_velocity.y = 1;
            break;
        case 77:
            m_velocity.x = 1;
            m_velocity.y = 0;
            break;
        case 75:
            m_velocity.x = -1;
            m_velocity.y = 0;
            break;
        }
    }
}
void Player::draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight)
{
    render(mapData, mapWidth, mapHeight);
}
void Player::die()
{
    destroy();
}
void Player::destroy()
{
    Game::removeEntity(getId());
}
