//
//  Game.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//  Copyright © 2017 Erik V. Ortega. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <array>

#include "Deck.hpp"
#include "Person.hpp"

class Game
{
protected:
    enum GameState {WELCOME, START, PLAY, END, WAIT};
    GameState m_state;
    Deck m_deck;
    Player m_player;
    Person m_dealer;
    size_t m_roundCount;
    std::string m_status_msg;
public:
    Game();
    virtual ~Game();
    
    void checkGame();
    
    void gameLoop();
    
    void initialiseRound();
    void finishRound();
    
    void dealerPlays();
    virtual void draw();
};

#endif /* Game_hpp */
