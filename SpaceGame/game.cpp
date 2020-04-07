#include "game.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "enemy.h"

//Static Elements
std::list<Entity*> Game::entities = std::list<Entity*>();
std::list<int> Game::deletedEntities = std::list<int>();

Game::Game()
{
}

Game::~Game()
{
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
        delete (*it);
	deletedEntities.clear();
}

//Entities Management
std::list<Entity*> Game::getEntitiesAtPoint(double x, double y)
{
    std::list<Entity*> hit;
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        if ((*it)->containsPoint(x, y))
            hit.push_back(*it);
    }
    return hit;
}
std::list<Entity*> Game::getEntitiesInRect(double x, double y, uint32_t width, uint32_t height)
{
    std::list<Entity*> hit;
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        if ((*it)->intersects(x, y, width, height))
            hit.push_back(*it);
    }
    return hit;
}

void Game::setUpGame()
{
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
        delete (*it);

    player = nullptr;
    entities.clear();
    enemies.clear();
    Entity::resetCounter();

    player = new Player(10.0, 10.0, 100.0, 10.0, 30.0, 0.2f, 10.0);
    entities.push_back(player);
    for (int i = 0; i < 5; i++)
    {
		Enemy* enemy = new Enemy(rand() % (MAP_WIDTH - 4), i * 2);
        entities.push_back(enemy);
        enemies.push_back(enemy);
    }
}

//Game Functionality
void Game::initialize()
{
    setUpGame();
}
void Game::processInput(char special, char input)
{
    if (player != nullptr)
        player->processInput(special, input);
}
void Game::update(double delta)
{
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
        (*it)->update(delta);
}
void Game::applyPhysics()
{
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
        (*it)->applyPhysics();
}
void Game::deleteObjects()
{
    if (deletedEntities.size() != 0)
    {
        for (std::list<int>::iterator itD = deletedEntities.begin(); itD != deletedEntities.end(); itD++)
        {
            for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
            {
                if ((*it)->getId() == (*itD))
                {
                    if ((*it)->getType() == EntityType::Player)
                        player = nullptr;
                    else if ((*it)->getType() == EntityType::Enemy)
                        enemies.remove(dynamic_cast<Enemy*>(*it));
                    delete (*it);
                    entities.erase(it);
                    break;
                }
            }
        }
        deletedEntities.clear();
    }
}
void Game::draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight)
{
    for (std::list<Entity*>::reverse_iterator it = entities.rbegin(); it != entities.rend(); it++)
        (*it)->draw(mapData, mapWidth, mapHeight);
}
bool Game::drawGUI()
{
    if (player != NULL)
    {
        printf("Your Health: %u          \n", uint32_t(player->getHealth()));
        printf("W/A/S/D or Arrows to move.\nF to stop.\nSpace to shoot.\nQ to quit.");
        if (enemies.size() == 0)
        {
            system("cls");
            printf("YOU WON!!!   :D\n\nR to play again.\nQ to Quit.\n\n");
            while(true)
            {
                char r = _getch();
                if (r == 'r' || r == 'R')
                {
                    setUpGame();
                    return true;
                }
                else if (r == 'q' || r == 'Q')
                    return false;
            }
        }
    }
    else
    {
        system("cls");
        printf("YOU LOSE!!!   D:\n\nR to try again.\nQ to Quit.\n\n");

        while(true)
        {
            char r = _getch();
            if (r == 'r' || r == 'R')
            {
                setUpGame();
                return true;
            }
            else if (r == 'q' || r == 'Q')
                return false;
        }
    }
    return true;
}
