//
//  Game.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#ifndef Game_hpp
#define Game_hpp

#include <array>

#include "Deck.hpp"
#include "Person.hpp"

class Game
{
private:
    
    void initialiseRound();
    void finishRound();
    
    void dealerPlays();
    void checkGame();
    
    virtual void draw() = 0;
    
protected:
    
    enum GameState {PLAY, DEALER_HAND, WAIT};
    
    struct GameScores
    {
        uint player;
        uint dealer;
        uint ties;
    } m_scores;
    
    GameState m_state;
    Deck m_deck;
    Person m_player;
    Person m_dealer;
    size_t m_roundCount;
    std::string m_status_msg;
    
public:
    enum RoundWinner {PLAYER, DEALER, TIE};
    
    Game();
    virtual ~Game();
    void gameLoop();
    
    static RoundWinner checkWinner(int points_player, int points_dealer);
};

#endif /* Game_hpp */
