//
//  main.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//  Copyright © 2017 Erik V. Ortega. All rights reserved.
//

//#include <iostream>
#include <array>
#include <vector>
#include <deque>

#include <unordered_map>
#include <assert.h>


#include "Card.hpp"
#include "Deck.hpp"
#include "VisualGame.hpp"






//using namespace  BlackJack;

int main(int argc, const char * argv[])
{
    
    VisualGame game;
    
    game.gameLoop();
    
    
    return 0;
}
