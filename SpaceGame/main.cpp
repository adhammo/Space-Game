//Programmer: Adham Mohamed Elhelly
//Date of Finish: 4/7/2020

//A simple Space Shooter Game made with C++ and a little bit of the standard windows libraries

/*
##########################################
#     <[]>                               #
#      ..              +                 #
#                      |            <[]> #
#            <[]>                    ..  #
#             ..             +     <[]>  #
#                            |      ..   #
#    <[]>                +               #
#     ..                 |               #
#                 <[]>                   #
#      ||          ..        +           #
#      ++                    |           #
#                                        #
#             ||         +               #
#             ++         |          ||   #
#                                   ++   #
#     ||                                 #
#     ++                 +               #
#                  ||    |               #
#                  ++    .               #
#                       <->              #
##########################################
*/

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "game.h"

void gotoxy(short x, short y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

void clenUp(char* mapData, Game* game)
{
    delete game;
    delete[] mapData;
}

int main()
{
    //Create game
    Game* game = new Game();

    //Initialize variables
    size_t i, j;
	char special = -1, key = -1;
    uint32_t startClock = 0;
	double delta = ONE_OVER_FPS;
    bool running = true;

    //Initialize containers
    char* mapData = new char[(MAP_WIDTH + 3) * MAP_HEIGHT];
	memset(mapData, 32, (MAP_WIDTH + 3) * MAP_HEIGHT * sizeof(char));
	for (i = 0; i < MAP_HEIGHT; i++)
	{
		mapData[(i * (MAP_WIDTH + 3)) + MAP_WIDTH] = BORDER;
		mapData[(i * (MAP_WIDTH + 3)) + MAP_WIDTH + 1] = '\n';
		mapData[(i * (MAP_WIDTH + 3)) + MAP_WIDTH + 2] = '\0';
	}


    //Game loop
    game->initialize();
    while (running)
    {
        //Record start time
        startClock = clock();

        //Check for next frame
        if (delta >= ONE_OVER_FPS)
        {
            //Clear mapData
            for (i = 0; i < MAP_HEIGHT; i++)
                for (j = 0; j < MAP_WIDTH; j++)
                    mapData[(i * (MAP_WIDTH + 3)) + j] = ' ';

            //Check if key is pressed
			special = -1;

			while (_kbhit())
			{
				//Process game input
				key = _getch();
				switch ((int)key)
				{
				case -32:
					special = -32;
					key = _getch();
					break;
				case (int)'q':
				case (int)'Q':
					running = false;
					break;
				default:
					special = 0;
				}
			}

			if (special != -1)
				game->processInput(special, key);

            //Update, apply physics, delete objects and draw game
            game->update(delta);
            game->applyPhysics();
            game->deleteObjects();
            game->draw(mapData, MAP_WIDTH + 3, MAP_HEIGHT);

            //Render
            gotoxy(0, 0);
            for (i = 0; i < MAP_WIDTH + 2; i++) //Top border
                std::cout << BORDER;
			std::cout << std::endl;
			for (i = 0; i < MAP_HEIGHT; i++) //Side borders and game
				std::cout << BORDER << (mapData + (i * (MAP_WIDTH + 3)));
            for (i = 0; i < MAP_WIDTH + 2; i++) //Bot border
				std::cout << BORDER;
			std::cout << std::endl;

            //Render GUI
            if (!game->drawGUI())
                running = false;

            //Reset delta
            delta = 0.0;
        }

        //Get delta
        delta += (clock() - startClock) * 0.001;
    }

    clenUp(mapData, game);
    return 0;
}
