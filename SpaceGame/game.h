#ifndef GAME_H
#define GAME_H

#include <list>
#include "player.h"
#include "enemy.h"

class Game
{
private: //Static Elements
	static std::list<Entity*> entities;
	static std::list<int> deletedEntities;

public:
    Game();
    ~Game();

public: //Functionality
    void initialize();
    void processInput(char special, char input);
    void update(double delta);
    void applyPhysics();
    void deleteObjects();
    void draw(char* mapData, uint32_t mapWidth, uint32_t mapHeight);
    bool drawGUI();

public:
    void setUpGame();

public: //Entities Management
    static void addEntity(Entity* entity) { Game::entities.push_back(entity); }
    static void removeEntity(uint32_t id) { deletedEntities.push_back(id); }
    static std::list<Entity*> getEntitiesAtPoint(double x, double y);
    static std::list<Entity*> getEntitiesInRect(double x, double y, uint32_t width, uint32_t height);

private:
    Player* player;
    std::list<Enemy*> enemies;
};

#endif // GAME_H
