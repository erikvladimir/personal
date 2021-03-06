//
//  main.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//


#include <string>

#include "VisualGame.hpp"

extern void RunTests();

int main(int argc, const char * argv[])
{
    // check and run tests
    if (argc == 2 && std::string(argv[1]).compare("test") == 0)
    {
        RunTests();
        return 0;
    }
    
    // run game
    Game * game = VisualGame::getInstance(); //singleton
    game->gameLoop();
    
    return 0;
}
